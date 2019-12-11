using System.Text;
using System.Collections.Generic;
using System.Linq;
using System;

namespace DEOS
{
	public class ChessTest
	{
		public static void Main(string[] args)
		{
			Console.WriteLine(Run());
		}
		public static bool Run()
		{
			DEOS deos = new DEOS();
			return deos.Run();
		}
	}
}