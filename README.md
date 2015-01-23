# StringData
Classe imitant les fonctionnalités de BitConverter (C#)

## Description
Extension Ruby codée en C++ pour récupérer/modifier des données natives dans un StringData (similaire au contenu d'un fichier). StringData est enfant de String donc a les même propriétés.

## Fonctions
* new(string) : Crée un StringData à partir d'un string
* ulong(pos) : retourne l'unsigned long se trouvant à la position pos
  <br> Exemple : StringData.new("\x00\x00\x00\x00\x01\x00\x00\x00").ulong(4) => 1
* set_ulong(pos, value) : modifie l'unisgned long
* long(pos) : retourne le long
* set_long(pos, value) : modifie le long
* ushort(pos) : retourne l'unsigned short
* set_ushort(pos, value) : modifie l'unsigned short
* short(pos) : retourne le short
* set_short(pos, value) : modifie l'unsigned short
* ubyte(pos) : récupère l'octet strictement positif
* set_ubyte(pos, value) : modifie l'octet stricteme strictement positif
* byte(pos) : récupère l'octet signé
* set_byte(pos) : modifie l'octet signé
* float(pos) : récupère le float
* set_float(pos, float_object) : modifie le float
* double(pos) : récupère le double
* set_double(pos, float_object) : modifie le double
  <br><b>Un float_object (Float) est un objet contenant un double en Ruby, aucun problème de conversion donc.</b>
* string(pos, size) : retourne le string de la taille size contenu dans le StringData
* set_string(pos, string) : modifie le string
