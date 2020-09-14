#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fstream> 



int buffer[8], bufferEscritura[8], in = 0, enc = 0, esc = 0, por_escribir = 0;
const int key = 0x12345678;
sem_t encript_cola, datos, datos_encript, sem_escritos;
pthread_mutex_t m, m_escritura;

void leer() 
{
	//espera a encript_cola
	
}

void escribir()
{
	//espera a datos_encript;
}


void* encriptar()
{
	//while (file_input.peek() != EOF) {
		sem_wait(&datos);
		sem_wait(&sem_escritos);

		pthread_mutex_lock(&m);



		int second_part = buffer[enc + 1], first_part = buffer[enc];
		enc = (enc + 2) % 8;

		pthread_mutex_unlock(&m);

		pthread_mutex_lock(&m_escritura);

		bufferEscritura[esc] = (second_part ^ key) ^ key;
		bufferEscritura[esc + 1] = (first_part ^ key) ^ key;

		esc = (esc + 2) % 8;

		pthread_mutex_unlock(&m_escritura);

		sem_post(&datos_encript);
		sem_post(&encript_cola);
	//}
}


