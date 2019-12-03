/*
 * TransientDetector.c
 *
 *  Created on: Jul 26, 2009
 *      Author: ghaitho
 */

#include "TransientDetector.h"
#include "Reducer.h"
#include "RawFrame.h"
#include "StateTable.h"
#include "Motion.h"
#include "Aircraft.h"
#include "Constants.h"
#include "helper.h"
#include "HashMap.h"
#include "VoxelMap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// FIXME: remove unused comments

float voxelSize;
RawFrame * currentFrame;
int motionctr = 0;

int frameno=-1;

Motion * createdMotions;

void TRANSIENTDETECTOR_init() {
	STATETABLE_init();
	voxelSize = GOOD_VOXEL_SIZE;
	VOXELMAP_init();
}

void TRANSIENTDETECTOR_freeCollisions (collisions * c) {
	collisions * ptr = c;
	collisions * ptr_next = 0;

	while (ptr != 0) {
		ptr_next = ptr->next;
		free (ptr->location);
		free (ptr);
		ptr = ptr_next;
	}
}

void TRANSIENTDETECTOR_run() {
	list_motions * l = 0;
	collisions * c  = (collisions *)malloc(sizeof(collisions));
	
	c->one = 0;
	c->two = 0;
	c->location = 0;
	c->next = 0;

	if (SYNCHRONOUS_DETECTOR || DEBUG_DETECTOR) {
		TRANSIENTDETECTOR_dumpFrame("CD-PROCESSING-FRAME (indexed as received):");
	}
	REDUCER_init(voxelSize);
	int numberOfCollisions = TRANSIENTDETECTOR_lookForCollisions(TRANSIENTDETECTOR_createMotions(),l,c);

	// printing all the detected collisions
	if (SYNCHRONOUS_DETECTOR || DEBUG_DETECTOR) {
		printf("CD detected %d collisions.\n",numberOfCollisions);
		int colIndex = 0;
		collisions * ptr = c;
		char buf1[20];
		while (ptr->next) {
			printf("CD collision %d occured at location %s with 2 involved aircraft.\n",colIndex,VECTOR3D_toString(buf1,ptr->location));
			printf("CD collision %d includes aircraft %s\n",colIndex,ptr->one->callsign);
			printf("CD collision %d includes aircraft %s\n",colIndex,ptr->two->callsign);
			colIndex++;
			ptr = ptr->next;
		}
	}
	TRANSIENTDETECTOR_freeCollisions (c);
//	printf("\n");

}

int TRANSIENTDETECTOR_lookForCollisions(Motion * m, list_motions * l, collisions * c) {

	l=TRANSIENTDETECTOR_reduceCollisionSet(m,l);

	//storing the number of suspected collisions
	int suspectedSize = 0;
	list_motions * mlist = l;
	while (mlist->next!=0){suspectedSize++;mlist=mlist->next;}

	if ((SYNCHRONOUS_DETECTOR || DEBUG_DETECTOR) && suspectedSize>0) {
		printf("CD found %d potential collisions\n",suspectedSize);
		int i=0;

		mlist = l;
		while (mlist->next!=0){
			int cnt = 0;
			motions * mm = mlist->val;
			while(mm->val){cnt++;mm=mm->next;}
			//printf("%d\n",cnt);
			mm = mlist->val;
			while (mm->val){
				printf("CD: potential collision %d (of %d aircraft) includes motion %s\n",i,cnt,MOTION_toString(mm->val));
				mm = mm->next;
			}
			i++;
			mlist=mlist->next;
		}

	}

	// Now we will determine if the suspected collisions are the real collisions
	mlist = l;
	int truesize = 0;
	while (mlist->next){
		truesize += TRANSIENTDETECTOR_determineCollisions(mlist->val,c);
		mlist = mlist ->next;
	}

	for (; l != 0; l = mlist) {
		mlist = l->next;

		for (
			motions *val_ptr = l->val, *val_next;
			val_ptr != 0;
			val_ptr = val_next
		) {
			val_next = val_ptr->next;
			free(val_ptr);
		}

		free(l);
	}

	for (int i = 0; i < currentFrame->planeCnt; ++i) {
		free(m[i].aircraft);
		free(m[i].pos_one);
		free(m[i].pos_two);
	}

	free(m);

	return truesize;

}

int itemscounter = 0;
int collect_motions_list(any_t * l, any_t * m) {
	list_motions * ll = (list_motions *)l;
	list_motions * ptr = 0, *newitem=0;
	motions * mm = (motions *)m;
	if(mm->next!=0) {
		//printf(" item number %d\n",itemscounter++);
		//printf(" motion %s suspected\n",MOTION_toString(mm->val));
		ptr = ll;
		while(ptr->next!=0)ptr=ptr->next;
		newitem = (list_motions *)malloc(sizeof(list_motions));
		newitem->val = 0;
		newitem->next  = 0;
		ptr->next = newitem;
		ptr->val = mm;
	}
	return MAP_OK;
}

void collectMotions(list_motions * ll) {
	list_motions * ptr = 0;
	int j=0,k=0;
	int listcount=0;
	VOXELMAP_initIter();
	while ((j = VOXELMAP_iterNext())!=-1) {
		listcount = VOXELMAP_getMotionCountUsingLocation(j);
		//listcount = VOXELMAP_iterNext();
		if (listcount>1) {
			ptr = ll;
			while(ptr->next!=0)ptr=ptr->next;
			ptr->next = (list_motions *)malloc(sizeof(list_motions));
			ptr->val = (motions *) malloc(sizeof(motions));
			motions * mm = ptr->val;
			ptr->next->val=0;
			ptr->next->next = 0;
			for (k=0;k<listcount;k++) {
				mm->next = (motions *) malloc(sizeof(motions));
				mm->next->next = 0;
				mm->next->val = 0;
				VOXELMAP_getUsingLocation(j,k,&(mm->val));
				mm=mm->next;
			}
		}
		//j++;
	}
}
/**
 * Takes a List of Motions and returns an List of Lists of Motions, where the inner lists implement RandomAccess.
 * Each Vector of Motions that is returned represents a set of Motions that might have collisions.
 */
list_motions * TRANSIENTDETECTOR_reduceCollisionSet(Motion * m,list_motions * l) {
	//map_t voxel_map;
	map_t graph_colors = hashmap_new();
//	int rr=0;
//	for(;rr<currentFrame->planeCnt;rr++) {
//		printf("motion: %s\n", MOTION_toString(&m[rr]));
//	}

	int motionIter = 0;
	Motion * motionptr=0;
	VOXELMAP_reset();
	for (motionIter=0;motionIter<motionctr;motionIter++) {
		motionptr = (Motion*)(m + motionIter*sizeof(Motion));
//		printf("processing motion %d %s\n",motionIter,MOTION_toString(&m[motionIter]));
		REDUCER_performVoxelHashing(&m[motionIter], graph_colors);
	}

//	rr=0;
//	for(;rr<currentFrame->planeCnt;rr++) {
//		printf("motion: %s\n", MOTION_toString(&m[rr]));
//	}


	if (graph_colors != 0) {
		hashmap_free(graph_colors);
	}


	l = (list_motions *)malloc(sizeof(list_motions));
	l->next=0;
	l->val=0;
	collectMotions(l);
	return l;
}

Motion * TRANSIENTDETECTOR_createMotions() {
	int i,pos,j;
	createdMotions = (Motion *) malloc(sizeof(Motion)*currentFrame->planeCnt);
	motionctr = 0;
	Vector3d * new_pos = 0;

	pos = 0;
	for (i = 0; i < currentFrame->planeCnt; i++) {

		float x = currentFrame->positions[3*i], y = currentFrame->positions[3*i + 1], z = currentFrame->positions[3*i + 2];
		
		// extract the call sign of plane i
		char* cs = (char *)malloc(currentFrame->lengths[i]+1);
		for (j = 0; j < currentFrame->lengths[i]; j++)
			cs[j] = currentFrame->callsigns[pos + j];
		cs[j] = 0;
		pos += currentFrame->lengths[i];
		CallSign * v = (CallSign *) malloc(sizeof(CallSign));
		v->length = j;
		v->val = cs;

		new_pos=(Vector3d*)malloc(sizeof(Vector3d));
		VECTOR3D_init2(new_pos,x,y,z);

		Vector3d * old_pos = (Vector3d *) malloc(sizeof(Vector3d));

		createdMotions[motionctr].aircraft = (Aircraft *) malloc(sizeof(Aircraft));
		
		createdMotions[motionctr].aircraft->callsign = cs;

		createdMotions[motionctr].pos_one = (Vector3d *) malloc(sizeof(Vector3d));
		createdMotions[motionctr].pos_two = (Vector3d *) malloc(sizeof(Vector3d));

		if (STATETABLE_get(v,old_pos) != MAP_OK) {
			// Ales : we have detected a new aircraft

			//here, we create a new callsign and store the aircraft into the state table.
			STATETABLE_put(v, new_pos->x, new_pos->y, new_pos->z);

			//MOTION_init2(&ret[motionctr], craft, new_pos);
			VECTOR3D_init2(createdMotions[motionctr].pos_one,new_pos->x,new_pos->y,new_pos->z);
			VECTOR3D_init2(createdMotions[motionctr].pos_two,new_pos->x,new_pos->y,new_pos->z);
			if (DEBUG_DETECTOR || SYNCHRONOUS_DETECTOR) {
				printf("createMotions: old position is null, adding motion: %s\n", MOTION_toString(&createdMotions[motionctr]));
			}
			motionctr++;

		} else {
			// this is already detected aircraft, we we need to update its position

			Vector3d * save_old_position = (Vector3d *) malloc(sizeof(Vector3d));
			VECTOR3D_init2(save_old_position,old_pos->x, old_pos->y, old_pos->z);

			//updating position in the StateTable
			VECTOR3D_set(old_pos,new_pos->x, new_pos->y, new_pos->z);
			STATETABLE_put(v, new_pos->x, new_pos->y, new_pos->z);

			//MOTION_init1(&ret[motionctr], craft, save_old_position, new_pos);
			VECTOR3D_init2(createdMotions[motionctr].pos_one,save_old_position->x,save_old_position->y,save_old_position->z);
			VECTOR3D_init2(createdMotions[motionctr].pos_two,new_pos->x,new_pos->y,new_pos->z);

			if (DEBUG_DETECTOR || SYNCHRONOUS_DETECTOR) {
				printf("createMotions: adding motion: %s\n", MOTION_toString(&createdMotions[motionctr]));
			}
			motionctr++;

			free(save_old_position);
		}

		free(cs);
		free(v);
		free(new_pos);
		free(old_pos);
	
	}
	return createdMotions;
}

void TRANSIENTDETECTOR_dumpFrame( char * debugPrefix ) {
	printFrame(frameno,debugPrefix, currentFrame->planeCnt, currentFrame->positions,
			currentFrame->lengths, currentFrame->callsigns);
}

void TRANSIENTDETECTOR_setFrame(RawFrame * f) {

	if (DEBUG_DETECTOR || DUMP_RECEIVED_FRAMES || SYNCHRONOUS_DETECTOR) {
		frameno++;
	}
	currentFrame = f;
	if (DUMP_RECEIVED_FRAMES) {
		TRANSIENTDETECTOR_dumpFrame( "CD-R-FRAME:");
	}
}

CallSign * TRANSIENTDETECTOR_getCallSign(CallSign * v, char * cs) {
	int len = strlen(cs);
	v->length = len;
	v->val = (char *) malloc(len);
	strcpy(v->val,cs);
	return v;
}

int TRANSIENTDETECTOR_checkCollisionsDuplicates(collisions * c,Motion * one, Motion * two) {
	while(c->next) {
		if (c->one==one->aircraft && c->two==two->aircraft)return 0;
		c=c->next;
	}
	return 1;
}

int TRANSIENTDETECTOR_determineCollisions(motions * mm, collisions * c) {
	int returned = 0;
	motions * m = mm, *m2 = mm;
	Vector3d * v = (Vector3d *) malloc(sizeof(Vector3d));
	while (m->next->next){
		m2 = m->next;
		while (m2->next) {
			// make sure we did not detect this before!!!
			if (TRANSIENTDETECTOR_checkCollisionsDuplicates(c,m->val,m2->val)) {
				// get vector3d collision
				if (MOTION_findIntersection(m->val,m2->val,v)) {
					collisions * ptr = c;
					while(ptr->next)ptr=ptr->next;
					ptr->next = (collisions *)malloc(sizeof(collisions));
					ptr->next->one = 0;
					ptr->next->two = 0;
					ptr->next->location = 0;
					ptr->next->next  = 0;

					ptr->one = m->val->aircraft;
					ptr->two = m2->val->aircraft;
					ptr->location = (Vector3d *) malloc(sizeof(Vector3d));
					VECTOR3D_init2(ptr->location,v->x,v->y,v->z);
					returned++;
				}
			}
			m2 = m2->next;
		}
		m = m->next;
	}
	free(v);
	return returned;
}
