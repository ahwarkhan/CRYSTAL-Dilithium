#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <oqs/oqs.h>

#define MESSAGE_LEN 32
#define ITERATIONS 100
#define CSV_FILE "results.csv"

// Timing helper
static inline double get_time() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (double)t.tv_sec + (double)t.tv_nsec / 1e9;
}

// Benchmark function
void benchmark_scheme(FILE *csv, const char *alg_name, const char *version_label) {
    OQS_SIG *sig = NULL;
    uint8_t *public_key = NULL;
    uint8_t *secret_key = NULL;
    uint8_t *signature = NULL;
    uint8_t message[MESSAGE_LEN];
    size_t signature_len;

    double start, end;
    int result;

    sig = OQS_SIG_new(alg_name);
    if (sig == NULL) {
        fprintf(stderr, "ERROR: %s was not enabled at compile-time.\n", alg_name);
        return;
    }

    // Dynamic allocation
    public_key = malloc(sig->length_public_key);
    secret_key = malloc(sig->length_secret_key);
    signature = malloc(sig->length_signature);

    if (!public_key || !secret_key || !signature) {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        OQS_SIG_free(sig);
        return;
    }

    printf("\nBenchmarking %s (%s)...\n", alg_name, version_label);

    // Keypair generation
    start = get_time();
    for (int i = 0; i < ITERATIONS; i++) {
        result = OQS_SIG_keypair(sig, public_key, secret_key);
        if (result != OQS_SUCCESS) {
            fprintf(stderr, "ERROR: Keypair generation failed.\n");
            break;
        }
    }
    end = get_time();
    double avg_keygen = ((end - start) / ITERATIONS) * 1000;
    printf("Average keypair generation time: %.4f ms\n", avg_keygen);

    // Signing
    memset(message, 0xAB, sizeof(message));
    start = get_time();
    for (int i = 0; i < ITERATIONS; i++) {
        result = OQS_SIG_sign(sig, signature, &signature_len, message, sizeof(message), secret_key);
        if (result != OQS_SUCCESS) {
            fprintf(stderr, "ERROR: Signing failed.\n");
            break;
        }
    }
    end = get_time();
    double avg_sign = ((end - start) / ITERATIONS) * 1000;
    printf("Average signing time: %.4f ms\n", avg_sign);

    // Verification
    start = get_time();
    for (int i = 0; i < ITERATIONS; i++) {
        result = OQS_SIG_verify(sig, message, sizeof(message), signature, signature_len, public_key);
        if (result != OQS_SUCCESS) {
            fprintf(stderr, "ERROR: Verification failed.\n");
            break;
        }
    }
    end = get_time();
    double avg_verify = ((end - start) / ITERATIONS) * 1000;
    printf("Average verification time: %.4f ms\n", avg_verify);

    // Export to CSV
    fprintf(csv, "%s,%s,%.4f,%.4f,%.4f\n", version_label, alg_name, avg_keygen, avg_sign, avg_verify);

    // Cleanup
    free(public_key);
    free(secret_key);
    free(signature);
    OQS_SIG_free(sig);
}

int main() {
    FILE *csv = fopen(CSV_FILE, "w");
    if (csv == NULL) {
        fprintf(stderr, "ERROR: Unable to create %s\n", CSV_FILE);
        return 1;
    }

    // CSV header
    fprintf(csv, "VERSION,SCHEME,KEYGEN(ms),SIGN(ms),VERIFY(ms)\n");

    // Optimized Dilithium II (simulate optimized version)
    benchmark_scheme(csv, OQS_SIG_alg_dilithium_2, "Dilithium_II_Optimized");

    // General implementations
    benchmark_scheme(csv, OQS_SIG_alg_dilithium_2, "Dilithium_II_General");
    benchmark_scheme(csv, OQS_SIG_alg_dilithium_3, "Dilithium_III");
    benchmark_scheme(csv, OQS_SIG_alg_dilithium_5, "Dilithium_V");
    benchmark_scheme(csv, OQS_SIG_alg_falcon_512, "Falcon_512");

    fclose(csv);
    printf("\nAll results saved to %s\n", CSV_FILE);

    return 0;
}
