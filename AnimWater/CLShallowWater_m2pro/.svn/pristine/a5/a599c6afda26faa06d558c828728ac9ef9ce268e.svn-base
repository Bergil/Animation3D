 
 
 

* Les dépendances du code
 - OpenGL/GLUT : cf doc du cours de rendu
 - cmake pour generer un makefile, un projet codeblocks ou un projet Visual
 - Le code a été testé sous Linux au Nautibus, un windows disposant de SVN/cmake/GLUT

 
* Pour compiler
 Compiler avec un Makefile 
     cd ....../GLUTGLBasicViewer/build
     /home/pers/alexandre.meyer/lib/Linux/cmake-2.8.3-Linux-i386/bin/cmake ..
     make

 Compiler avec codeblocks 
     cd ....../GLUTGLBasicViewer/build
     /home/pers/alexandre.meyer/lib/Linux/cmake-2.8.3-Linux-i386/bin/cmake -G "CodeBlocks - Unix Makefiles" ..
     codeblocks
     ouvrir le projet GLUTGLBasicViewer.cbp dans ..../GLUTGLBasicViewer/build

 - La class CAViewer contient les fonctions init/draw qui s'occupent de l'affichage
 - Pour ajouter des fichiers au projet, regarder ..../GLUTGLBasicViewer/CMakeLists.txt
 - Pour la 3e partie du TP, ce code utilise libBullet qui est dans ~alexandre.meyer/lib/Linux/bullet. Pour désactiver Bullet, editer le fichier ..../CharAnim/CMakeLists.txt et indiquer "NO" devant "WITH_BULLET".