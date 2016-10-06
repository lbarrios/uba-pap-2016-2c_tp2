#!/usr/bin/env bash
COLORDIFF=$(which colordiff)
if [ $? -eq 0 ]; then
	DIFF_CMD=colordiff
else
	echo -e "\e[32mPara una mejor experiencia(?), instalar colordiff\e[39m"
	echo -e "\e[32mEn ubuntu/debian, debería bastar con 'sudo apt-get install colordiff'\e[39m\n"
	DIFF_CMD=diff
fi

ejercicio=${PWD##*/}
if [ -f ${ejercicio}.py ]; then
	ejercicio_ejecutable="python3 -O ${ejercicio}.py"
else
	ejercicio_ejecutable=./${ejercicio}
fi

# Check if there is an output for every input, if not fail-exit
inputs=inputs/*.txt
for input_path in ${inputs}; do
	input=${input_path##*/}
	if [ ! -f outputs/${input} ]; then
		echo "Los tests para '${ejercicio}' no se han podido correr"
		echo "El output correspondiente al input '${input}' no existe"
		exit 1
	fi
done

# Create run test for every input and compare with every output
for input_path in ${inputs}; do
	input_filename=${input_path##*/}
	echo -n "Comparando el resultado de './${ejercicio} < ${input_path}' contra 'outputs/${input_filename}'..."
	diff=$(${DIFF_CMD} -y <(${ejercicio_ejecutable} < ${input_path}) outputs/${input_filename})
	if [ $? -eq 0 ]; then
		echo -e "\e[1m\e[32mOK!\e[39m\e[0m"
	else
		echo -e "\e[1m\e[31mMAL!\e[39m\e[0m"
		echo -e "\n\e[91mError en el input ${input_filename}...\e[39m\e[0m"
		echo -e "Resultado del diff: (izquierda: output del programa, derecha: output esperado)\n${diff}"
		echo "Error en el ejercicio ${ejercicio}"
		exit 1
	fi
done
