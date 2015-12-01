using System;
using System.IO;
using System.Linq;
using WebSupergoo.ABCpdf10;
using WebSupergoo.ABCpdf10.Objects;
 
namespace abcPDF
{
    class MainClass
    {
        public static void Main(string[] args)
        {
        	Doc pdfDoc = new Doc();
        	pdfDoc.Read(@"C:\ton\chemin\vers\ton\pdf.pdf");
        	pdfDoc.Rendering.DotsPerInch = 36;
        	String defaultName = "PAGE_";
        	String format = ".tif";
        	String pathTiff = @"C:\Users\orsery\Desktop\PDFCouleur\abcppdf\CEDRIC_01_40665-P7";
        	var directory = new DirectoryInfo(pathTiff);
        	if(directory. Exists)
            {
        	for (int i = 1; i <= pdfDoc.PageCount; i++)
			{ 
				pdfDoc.PageNumber = i;
  				pdfDoc.Rect.String = pdfDoc.CropBox.String;
  				pdfDoc.Rendering.SaveAppend = (i != 1);
  				pdfDoc.Rendering.SaveCompression = XRendering.Compression.G4;
  				pdfDoc.Rendering.Save(pathTiff+"\\"+defaultName+i+format);
			}
			pdfDoc.Clear();

           	var theDoc = new Doc();
            var directory = new DirectoryInfo(pathTiff);
        	
        		foreach (FileInfo f in directory.GetFiles().OrderBy(fi=>fi.FullName))
        		{
                	theDoc.Page = theDoc.AddPage();
            		var i = theDoc.AddImageFile(f.FullName ,1);  
            		var im = (ImageLayer)theDoc.ObjectSoup[i];
            		im.PixMap.ToGrayscale();
        		}
 
         	theDoc.Save(@"C:\Users\orsery\Desktop\PDFCouleur\abcppdf\CEDRIC_01_40665-P7.pdf");
            theDoc.Clear();
            Console.WriteLine("good");
        }
        else
        {
            Console.WriteLine("DIRECTORY DON'T EXISTS");
        }
}
   }
}