#include<stdio.h>

int main(){
    int vetor[10] = {1,2,3,4,5,6,7,8,9,10};
    int leitor;
    FILE *exemplo;

    exemplo = fopen("teste.bin", "wb");


    for(int i=0; i<10; i++){
        fwrite(&vetor[i], sizeof(int), 1, exemplo);
    }

    fclose(exemplo);

    exemplo = fopen("teste.bin", "rb");
    if(exemplo == NULL){
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    printf("Numero: ");
    while(!feof(exemplo)){
        fread(&leitor, sizeof(int), 1, exemplo);
        printf("%d ", leitor);
    }

    fclose(exemplo);
    exemplo = fopen("teste.bin", "rb+");
    if(exemplo == NULL){
        printf("Erro no append\n");
        return;
    }

    fseek(exemplo, 2*sizeof(int), SEEK_SET);
    leitor = 987;
    fwrite(&leitor, sizeof(int), 1, exemplo);
    fseek(exemplo, 0, SEEK_SET);

    printf("\nNumero dnv: ");
    while(!feof(exemplo)){
        fread(&leitor, sizeof(int), 1, exemplo);
        printf("%d ", leitor);
    }

    fclose(exemplo);
    return 0;
}
