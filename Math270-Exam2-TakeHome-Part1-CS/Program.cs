using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathNet.Numerics.LinearAlgebra;
namespace Math270_Exam2_TakeHome_Part1_CS
{
   
    
    class Program
    {
        static int Encode(char c)
        {
            int v = 0;
            c = Char.ToLower(c);
            if (c >= 'a' && c <= 'z') v = (c - 'a') + 1;
            else if (c == ' ') v = 27;
            else throw new NotSupportedException();
            return v;
        }
        static char Decode(int v)
        {
            char c = '\0';
            if (v == 27) c = ' ';
            else if (v >= 1 && v <= 26) c = (char)((v - 1) + 'a');
            else throw new NotSupportedException();
            return c;
        }
        static string Encrypt(string plainText,Matrix<double> xfm)
        {
            if (plainText == null) throw new ArgumentNullException(nameof(plainText));
            if (plainText.Length == 0) return "";
            int dangle = plainText.Length % 4;
            if (dangle != 0) plainText += new string(' ', 4 - dangle);
            int chunkCount = plainText.Length / 4;
            return Enumerable.Range(0, chunkCount)
                .Select(chunkIdx => plainText.Substring(chunkIdx * 4, 4)) 
                .Select(chunk => Vector<double>.Build.DenseOfEnumerable(chunk.Select(c => (double)Encode(c))))
                .Select(ptv => xfm.Multiply(ptv).Modulus(27))
                .Select(ctv => ctv.Aggregate(new StringBuilder(), (bldr, elem) => bldr.Append(Decode((int)elem)), bldr => bldr.ToString()))
                .Aggregate(new StringBuilder(), (bldr, elem) => bldr.Append(elem), bldr => bldr.ToString());

        } 
        static void Main(string[] args)
        {
            var encryptXfm = Matrix<double>.Build.DenseOfColumnArrays(
                new double[] { 2, -1, 0, 0 }, new double[] { 1, 1, -2, 0 },
                new double[] { 3, -2, 1, 1 }, new double[] { 1, 0, 1, 4 });
            var decyrptXfm = encryptXfm.Inverse();
            string plainText = "EXAMPLE MESSAGE";
            string cipherText = Encrypt(plainText, encryptXfm);
            string decodedText = Encrypt(cipherText, decyrptXfm);
            Console.WriteLine(plainText);
            Console.WriteLine(cipherText);
            Console.WriteLine(decodedText);



        }
    }
}
