/*
 * main.cpp
 *
 *  Created on: 8 mars 2013
 *      Author: engel
 */

#include "constantes.h"
#include "enregistreur_fichier.h"
#include "enregistreur_fichier_texte.h"
#include "harmonique.h"
#include "signal_constant.h"
#include "Multiplicateur.h"
#include "Volume.h"
#include "operation_binaire.h"
#include "Mixeur.h"
#include "VolumeCompose.h"
#include "FadeIn.h"
#include "lecteur_fichier.h"
#include "Compresser.h"
#include "Echo.h"
#include <iostream>
#include <functional>

void
q2_signal_constant() {
  signal_constant sc(0.5);
  enregistreur_fichier_texte enr("02_sc.txt", 1);
  enr.connecterEntree(sc.getSortie(0), 0);
  // générer 5 valeurs
  for (unsigned int i = 0; i < 5; ++i) {
    sc.calculer();
    enr.calculer();
  }
}

void q7_harmonique() {
  harmonique h(440);					// la 440Hz
  enregistreur_fichier enr("07_harmonique.raw", 1);	// fichier mono

  enr.connecterEntree(h.getSortie(0), 0);
  // produire 2 secondes de son
  for (unsigned long int i = 0; i < 2 * MixageSonore::frequency; ++i) {
    h.calculer();
    enr.calculer();
  }
}


void q8_multiplicateur()
{
	operation_binaire<std::multiplies<double> > mul;
	harmonique h1(440);
	mul.connecterEntree(h1.getSortie(0), 0);
	harmonique h2(880);
	mul.connecterEntree(h2.getSortie(0), 1);
	
	enregistreur_fichier enr("08_mul.raw", 1);
	enr.connecterEntree(mul.getSortie(0), 0);
	for (unsigned long int i = 0; i < 2 * MixageSonore::frequency; ++i) {
		h1.calculer();
		h2.calculer();
		mul.calculer();
		enr.calculer();
	}
}

void q12_volume()
{
	Volume vol(0.3);
	harmonique h1(440);
	vol.connecterEntree(h1.getSortie(0), 0);
	
	enregistreur_fichier enr("12_vol.raw", 1);
	enr.connecterEntree(vol.getSortie(0), 0);
	for (unsigned long int i = 0; i < 2 * MixageSonore::frequency; ++i) {
		h1.calculer();
		vol.calculer();
		enr.calculer();
	}
}

void q14_VolumeCompose()
{
	harmonique h(440);
	VolumeCompose v(0.5);

	v.connecterEntree(h.getSortie(0), 0);

	enregistreur_fichier enr("14_volumeCompose.raw", 1);
	enr.connecterEntree(v.getSortie(0), 0);

	for (unsigned long int i = 0; i < 2 * MixageSonore::frequency; ++i)
	{
		h.calculer();
		v.calculer();
		enr.calculer();
	}
}

void q15_Mixeur()
{
	harmonique h1(440);
	harmonique h2(600);
	harmonique h3(880);

  double t[] =  {0.5, 0.5, 0.5};

  Mixeur m(3, t);
  m.connecterEntree(h1.getSortie(0), 0);
  m.connecterEntree(h2.getSortie(0), 1);
  m.connecterEntree(h3.getSortie(0), 2);

	enregistreur_fichier enr("15_mixeur.raw", 1);
	enr.connecterEntree(m.getSortie(0), 0);

	for (unsigned long int i = 0; i < 2 * MixageSonore::frequency; ++i)
	{
		h1.calculer();
	  h2.calculer();
	  h3.calculer();
	  m.calculer();
	  enr.calculer();
	}
}

void q16_MixeurSignaux()
{
	try
	{
		//lecteur_fichier l1("raw/mono.raw",1);
		lecteur_fichier l2("raw/stereo.raw",2);
		
		double t[] =  { 1, 1};
		Mixeur m(2, t);
		m.connecterEntree(l2.getSortie(0), 0);
		m.connecterEntree(l2.getSortie(1), 1);
	//	m.connecterEntree(l2.getSortie(1), 2);

		enregistreur_fichier enr("16_mixeurSignaux.raw", 1);
		enr.connecterEntree(m.getSortie(0), 0);

		for (unsigned long int i = 0; i < 10 * MixageSonore::frequency; ++i)
		{
			try
			{
			//	l1.calculer();
				l2.calculer();
			}
			catch (std::exception& e)
		  {
		    std::cerr << e.what() << '\n';
		    break;
		  }
			m.calculer();
			enr.calculer();
		}
	}
	catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
}

void bonus_electroMix()
{
	try
	{
		lecteur_fichier l1("raw/stereo.raw",2);
		
		double t[] =  {1, 1};
		Mixeur m(2, t);
		m.connecterEntree(l1.getSortie(0), 0);
		m.connecterEntree(l1.getSortie(1), 1);

		enregistreur_fichier enr("electroMix.raw", 1);
		enr.connecterEntree(m.getSortie(0), 0);

		for (unsigned long int i = 0; i < 10 * MixageSonore::frequency; ++i)
		{
			try
			{
				l1.ElectroSummerMixCalc();
			}
			catch (std::exception& e)
		  {
		    std::cerr << e.what() << '\n';
		    break;
		  }
			m.calculer();
			enr.calculer();
		}
	}
	catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
}

void FadeInf()
{
	operation_binaire<std::multiplies<double> > mul;
	harmonique h1(440);
	FadeIn f(2);
	mul.connecterEntree(h1.getSortie(0), 0);
	mul.connecterEntree(f.getSortie(0), 1);
	
	enregistreur_fichier enr("FadeIn.raw", 1);
	enr.connecterEntree(mul.getSortie(0), 0);
	for (unsigned long int i = 0; i < 2 * MixageSonore::frequency; ++i) {
		h1.calculer();
		f.calculer();
		mul.calculer();
		enr.calculer();
	}
}

void Compresse()
{
	harmonique h(2600);
	Compresser c(0.5);

	c.connecterEntree(h.getSortie(0), 0);

	enregistreur_fichier enr("Compresse.raw", 1);
	enr.connecterEntree(c.getSortie(0), 0);

	for (unsigned long int i = 0; i < 2 * MixageSonore::frequency; ++i)
	{
		h.calculer();
		c.calculer();
		enr.calculer();
	}
}

void Echof()
{
	try
	{
		lecteur_fichier l1("raw/mono.raw",1);
		Echo e(0.5);

		e.connecterEntree(l1.getSortie(0), 0);

		enregistreur_fichier enr("Echo.raw", 1);
		enr.connecterEntree(e.getSortie(0), 0);

		for (unsigned long int i = 0; i < 2 * MixageSonore::frequency; ++i)
		{
			try
			{
				l1.calculer();
			}
			catch (std::exception& e)
		  {
		    std::cerr << e.what() << '\n';
		    break;
		  }
			e.calculer();
			enr.calculer();
		}
	}	
	catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
}

int
main() {
//  q2_signal_constant();
//  q7_harmonique();
//  q8_multiplicateur();  
//  q12_volume();
//  q14_VolumeCompose();
//  q15_Mixeur();
  q16_MixeurSignaux();
//  FadeInf();
//  Compresse();
//  Echof();
	bonus_electroMix();
  return 0;
}
