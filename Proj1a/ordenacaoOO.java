package Proj1a;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class ordenacaoOO {
    private static final int TAM = 100;
    private static final int REPETICOES = 1024;

    public static void insertionSort(int[] arr, int tamanho) {
        int i, j, aux;
        for (i = 1; i < tamanho; i++) {
            aux = arr[i];
            j = i - 1;

            while (j >= 0 && arr[j] > aux) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = aux;
        }
    }

    public static void geradorDeVetor(int[] arr, int tamanho) {
        Random rand = new Random();
        for (int i = 0; i < tamanho; i++) {
            arr[i] = rand.nextInt(1000);
        }
    }

    public static void main(String[] args) {
        try {
            FileWriter arquivo = new FileWriter("resultadosEmJava.csv");

            for (int a = 0; a < REPETICOES; a++) {
                int[] vetor = new int[TAM];
                
                for (int i = 0; i < REPETICOES; i++) {
                    geradorDeVetor(vetor, TAM);
                }
                long inicio = System.nanoTime();
                for (int i = 0; i < REPETICOES; i++) {
                    insertionSort(vetor, TAM);
                }
                long fim = System.nanoTime();
                double tempo = (double) (fim - inicio) / 1_000_000_000;
                arquivo.write(String.format("%f%n", tempo));
            }
            arquivo.close();
            System.out.println("Os resultados foram salvos em 'resultadosEmJava.csv'.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
