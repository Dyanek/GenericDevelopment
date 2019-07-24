LD=g++
CXX=g++ -g -c

EXEC_SRC=\
	testGrayLevelImage2DPartie2.cpp testColorImage2DPartie3.cpp testColorImage2DPartie4.cpp testColorImage2DPartie5.cpp testGrayLevelImage2DPartie5.cpp save-green-channel.cpp save-channels.cpp invert-red-blue.cpp cathode-ray-effect.cpp egaliseur-couleur.cpp filtre-sepia-color.cpp filtre-sepia-graylevel.cpp histogramme.cpp

MODULE_SRC=\

MODULE_OBJ=${MODULE_SRC:.cpp=.o}
EXEC_OBJ=${EXEC_SRC:.cpp=.o}

EXEC_PRG=${EXEC_SRC:.cpp=}

all: ${EXEC_PRG} ${MODULE_OBJ} ${EXEC_OBJ}

testGrayLevelImage2DPartie2: testGrayLevelImage2DPartie2.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

testColorImage2DPartie3: testColorImage2DPartie3.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

testColorImage2DPartie4: testColorImage2DPartie4.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

testColorImage2DPartie5: testColorImage2DPartie5.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

testGrayLevelImage2DPartie5: testGrayLevelImage2DPartie5.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

save-green-channel: save-green-channel.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

save-channels: save-channels.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

invert-red-blue: invert-red-blue.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

cathode-ray-effect: cathode-ray-effect.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

egaliseur-couleur: egaliseur-couleur.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

filtre-sepia-color: filtre-sepia-color.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

filtre-sepia-graylevel: filtre-sepia-graylevel.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

histogramme: histogramme.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

.cpp.o: %.cpp %.hpp
	${CXX} $<

clean:
	rm -f ${EXEC_PRG} ${MODULE_OBJ} ${EXEC_OBJ}

