# webcam_point_features

ORB

ORB són les sigles de Oriented FAST and Rotated BRIEF). És un algoritme de detecció utilitzat per tasques de visió per computador, com el reconeixement d’objectes o reconstruccions en 3D.
Aquest, pertany a la llibreria OpenCV i és una bona alternativa per subsituit el SIFT(Scale-invariant feature transofrm) i el SURF (Speeded-Up Robust Features), per els cuals s’ha de pagar ja que estan patentats. El SIFT és un algoritme per extreure punts d’interes d’una imatge, com per exemple, una vora o textura. El SURF és un algoritme similar al SIFT però amb el que es poden obtenir millors resultats.

ORB está basat en els métodes FAST i BRIEF, El FAST s’utilitza per reconeixer punts clau, després s’aplica la mesura Harris corner per obtenir els millors punts. El problema és que no té en compte la orientació.

L’algoritme ORB ve a ser la combinació del FAST i el BRIEF però tenint en compte la rotació, gràcies a la distància de Hamming.
Es calcula la intenstat del centreID i s’obté una matriu, el centre de masses. Per calcular la orientació d’un punt es calcula el vector del punt al centreID. L’orientació ve donada per l’angle del vector respecte al centreID.

Per utilitzar l’algoritme ORB és necessari crear un objecte ORG amb la funció cv2.ORB() o bé fent servir la interfície feature 2d i definir els parametres necessaries, tots ells opcionals.



Referències

- http://scikit-image.org/docs/dev/auto_examples/plot_orb.html
- https://es.wikipedia.org/wiki/SURF
- https://es.wikipedia.org/wiki/Scale-invariant_feature_transform 
- https://gilscvblog.com/2013/10/04/a-tutorial-on-binary-descriptors-part-3-the-orb-descriptor/
- https://en.wikipedia.org/wiki/Features_from_accelerated_segment_test
- https://en.wikipedia.org/wiki/ORB_(feature_descriptor)
- http://docs.opencv.org/3.0-beta/doc/py_tutorials/py_feature2d/py_orb/py_orb.html
