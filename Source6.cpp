#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include <xmmintrin.h> 
#include <intrin.h>

void aduna2Vect(float a[4], float b[4], float c[4]){
	for (int i = 0; i < 4; i++){
		c[i] = a[i] + b[i];
	}
}
void aduna2VectorRapid(float a[4], float b[4], float c[4]){
	__m128 m, m_result;
	__m128 arr1;
	__m128 arr2;
	arr1 = _mm_load_ps(a);
	arr2 = _mm_load_ps(b);
	m_result = _mm_add_ps(arr1, arr2);
	_mm_store_ps(c, m_result);
}


void vectScalar(float a[4], float sc){
	for (int i = 0; i < 4; i++){
		a[i] = a[i] * sc;
	}
}


void matriceVector(float a[4][4], float b[4], float c[4]){
	float s = 0;
	for (int i = 0; i < 4; i++){
		s = 0;
		for (int j = 0; j < 4; j++){
			s += a[i][j] * b[j];
		}
		c[i] = s;
	}
}

void matriceMatrice(float a[4][4], float b[4][4], float c[4][4]){
	float s = 0.0;
	for (int i = 0; i < 4; i++){
		
		for (int j = 0; j < 4; j++){
			s = 0.0;
			for (int k = 0; k < 4; k++){
				s += a[i][k] * b[k][j];
			}
			c[i][j] = s;
		}
	}
}
float main(){
	float a[4][4], b[4][4], c[4][4];
	a[0][0] = 1.0;
	a[0][1] = 2.0;
	a[0][2] = 3.0;
	a[0][3] = 4.0;
	a[1][0] = 5.0;
	a[1][1] = 6.0;
	a[1][2] = 7.0;
	a[1][3] = 8.0;
	a[2][0] = 1.0;
	a[2][1] = 2.0;
	a[2][2] = 3.0;
	a[2][3] = 4.0;
	a[3][0] = 5.0;
	a[3][1] = 6.0;
	a[3][2] = 7.0;
	a[3][3] = 8.0;

	b[0][0] = 1.0;
	b[0][1] = 2.0;
	b[0][2] = 3.0;
	b[0][3] = 4.0;
	b[1][0] = 5.0;
	b[1][1] = 6.0;
	b[1][2] = 7.0;
	b[1][3] = 8.0;
	b[2][0] = 1.0;
	b[2][1] = 2.0;
	b[2][2] = 3.0;
	b[2][3] = 4.0;
	b[3][0] = 5.0;
	b[3][1] = 6.0;
	b[3][2] = 7.0;
	b[3][3] = 8.0;
	
	float temp1[]  = { 1.1, 1.2, 1.3, 14.5};
	float temp2[] = { 1.2, 2.3, 3.4, 3.5};
	float temp3[4];
	float d[4];
	__m128 m, m_result;
	__m128 arr1;
	__m128 arr2,arr3;
	clock_t start, end;
	float seconds;
	//aduna vector cu vector
	//varianta inceata
	printf("Adunare vector cu vector instructiuni normale :");
	 start = clock();
	for (int i = 0; i < 1000000; i++) { aduna2Vect(temp1, temp2, temp3); }
	 end = clock();
	 seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("%f secunde\n\n", seconds);


	//varianta rapida
	printf("Adunare vector cu vector instructiuni SSE ");
	start = clock();
	for (int i = 0; i < 1000000; i++) {
		arr1 = _mm_load_ps(temp1);
		arr2 = _mm_load_ps(temp2);
		m_result = _mm_add_ps(arr1, arr2);
		_mm_store_ps(temp3, m_result);
	}
	end = clock();
	 seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("%f secunde\n\n", seconds);
	
	//end aduna vector cu vector


	// vector scalar
	//varianta inceata
	printf("Inmulteste vector cu scalar instructiuni normale ");
	start = clock();
	for (int i = 0; i < 1000000; i++) {
		temp1[0] = 1;
		temp1[1] = 2;
		temp1[2] = 3;
		temp1[3] = 4;
		vectScalar(temp1, 10.0);
	}
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;

	printf("%f secunde\n\n", seconds);
	//varianta rapida
	printf("Inmulteste vector cu scalar instructiuni SSE ");
	start = clock();
	for (int i = 0; i < 1000000; i++) {
		arr1 = _mm_load_ps(temp1);
		arr2 = _mm_set1_ps(10);
		m_result = _mm_mul_ps(arr1, arr2);
		_mm_store_ps(temp1, m_result);
	}
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("%f secunde\n\n", seconds);
	//end vector scalar


	// matrice vector
	//varianta inceata
	printf("Inmultire matrice vector instructiuni normale ");
	start = clock();
	for (int i = 0; i < 1000000; i++) {
		matriceVector(a, temp2, temp3);
	}
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("%f secunde\n\n", seconds);
	//varianta rapida
	printf("Inmultire matrice vector instructiuni SSE ");
	start = clock();
	for (int k = 0; k < 100000; k++) {
		arr2 = _mm_load_ps(temp2);
		arr3 = _mm_set1_ps(0);
		float aux[] = { 0.0, 0.0, 0.0, 0.0 };
		float aux2[4];
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				aux2[j] = a[i][j];
			}
			arr1 = _mm_load_ps(aux2);
			m_result = _mm_mul_ps(arr1, arr2);
			m_result = _mm_hadd_ps(m_result, arr3);
			m_result = _mm_hadd_ps(m_result, arr3);
			temp3[i] = m_result.m128_f32[0];
		}
	}
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("%f secunde\n\n", seconds);
	//end vector matrice


	// matrice matrice
	//varianta inceata
	printf("Inmultire matrice matrice instructiuni normale ");
	start = clock();
	for (int i = 0; i < 100000; i++) {
		matriceMatrice(a, b, c);
	}
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("%f secunde\n\n", seconds);
	float aux[4];
	float aux2[4];
	//varianta rapida
	printf("Inmultire matrice matrice instructiuni SSE ");
	start = clock();
	for (int l = 0; l < 10000; l++) {
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				for (int k = 0; k < 4; k++){
					aux[k] = a[i][k];
					aux2[k] = a[k][j];
				}
				arr1 = _mm_load_ps(aux);
				arr2 = _mm_load_ps(aux2);
				m_result = _mm_mul_ps(arr1, arr2);
				m_result = _mm_hadd_ps(m_result, arr3);
				m_result = _mm_hadd_ps(m_result, arr3);
				c[i][j] = m_result.m128_f32[0];
			}
		}
	}
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("%f secunde\n\n", seconds);
	//end matrice matrice

	system("pause");
	return 0;
}