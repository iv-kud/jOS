extern "C" void kernel_main() {
    const char* hello = "Hello JustOS!";
    char* vide_memory = (char*) 0xB8000;
    for (int i = 0; hello[i] != '\0'; i++)
    {
        vide_memory[i * 2] = hello[i];
        vide_memory[i * 2 + 1] = 0x0A;
    }

    while(true);
}
