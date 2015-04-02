SELECT * FROM Enseignant;

SELECT Enseignant_idEnseignant FROM Enseigne WHERE Cours_idCours = 1;
SELECT horaire FROM estDans WHERE Cours_idCours = 2;
SELECT * FROM Etudiant WHERE Parcours_idPar = 2;
SELECT * FROM estDans WHERE Salle_idSalle = 20;

SELECT horaire FROM estDans WHERE Cours_idCours = (SELECT idCours FROM estInscrit WHERE idEtudiant = 1) AND horaire > '2010';
SELECT horaire FROM estDans WHERE Cours_idCours = (SELECT Cours_idCours FROM Enseigne WHERE Enseignant_idEnseignant = 1);

SELECT nom, prenom FROM estInscrit EI, Etudiant E 
WHERE  EI.idEtudiant = E.idEtudiant AND E.Parcours_idPar = 1
AND EI.idCours = 1;
select * from estInscrit;

INSERT INTO estDans VALUES(2,1,'2015-05-05 05:05:05');
SELECT DISTINCT Salle_idSalle, horaire FROM estDans WHERE horaire > '2014' AND horaire < '2016';