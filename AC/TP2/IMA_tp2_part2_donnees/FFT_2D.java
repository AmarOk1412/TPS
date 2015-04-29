import java.io.IOException;

public class FFT_2D {

	//renvoie la TFD d'une image de complexes
	public static CpxImg FFT(CpxImg I) {

		CpxImg out = new CpxImg(I.taille());

		// FFT 1D sur les lignes
		for (int k = 0; k < I.taille(); k++)
			out.set_line(k,FFT_1D.FFT(I.get_line(k)));
		  
		// transposition
		out.transpose();

		// FFT 1D sur les "nouvelles" lignes de out (anciennes colonnes)
		for (int k = 0; k < I.taille(); k++)
			out.set_line(k,FFT_1D.FFT(out.get_line(k)));

		//on re transpose pour revenir dans le sens de depart
		out.transpose();
		
		//on divise par la taille de I
		out.multiply(1./I.taille());
		return out.recentrage();
	}
	
	//renvoie la TFD inverse d'une images de complexes
	public static CpxImg FFT_inverse(CpxImg I) {
		I = I.recentrage();
		CpxImg out = new CpxImg(I.taille());
		for (int k = 0; k < I.taille(); k++)
			out.set_line(k, I.get_line(k).conjuge());

		out = FFT(out).recentrage();
		for (int k = 0; k < I.taille(); k++)
			out.set_line(k, out.get_line(k).conjuge());
		return out;
	}

	//compression par mise a zero des coefficients de frequence > k
	// FI contient la TDF de I 
	public static void compression(CpxImg FI, int k) {
		int n = FI.taille();
		for(int i = 0; i < n; ++i)
		{
			if(i < (n/2)-k || i > (n/2)+k)
			{
				CpxTab newline = new CpxTab(n);
				FI.set_line(i, newline);
			}
			else
			{
				CpxTab newline = new CpxTab(n);
				for(int j = (n/2)-k; j < (n/2)+k; ++j)
				{
					newline.set_p_reel(j, FI.get_p_reel(i,j));
					newline.set_p_imag(j, FI.get_p_imag(i,j));
				}
				FI.set_line(i, newline);
			}
		}
	}
	
	public static int compression_seuil(CpxImg FI, double seuil){
		int n = FI.taille();
		seuil = (seuil/100)*255;
		int coeffSign = 0;
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < n; ++j)
			{
				double reel = FI.get_p_reel(i, j);
				double img  = FI.get_p_imag(i, j);
				double module = Math.sqrt(reel*reel + img*img);
				if(module < seuil)
				{
					FI.set_p_reel(i, j, 0);
					FI.set_p_imag(i, j, 0);
				}
				else
					++coeffSign;
			}
		}
		return coeffSign;
	}

	
	public static void main(String[] args) {
		
		try {			
			//PLACEZ ICI VOS TESTS en 2D
			//Exemple, lecture
			BytePixmap BP = new BytePixmap("fingerprint.pgm");
			CpxImg I = new CpxImg(BP);
			I = FFT(I);
			//Exemple, ecriture
//			compression(I, 128);
			System.out.println(compression_seuil(I, 25));
			BP = I.convert_to_BytePixmap();
			BP.write("fingerprint_compresse_seuil.pgm");
			I = FFT_inverse(I);
			//Exemple, ecriture
			BP = I.convert_to_BytePixmap();
			BP.write("fingerprint_FFT_Inv_compresse_seuil.pgm");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
