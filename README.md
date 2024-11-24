# C* Labs
- ## Build
    ```bash
    make
    ```
- ## Usage
    - **Server**
    ```bash
    ./c_labs_server <run/help> <ip> <port> <thread_count>
    ```
    - **Client**
    ```bash
    ./c_labs_client <ip> <port>
    ```
- ## Output
    - **Starting server**
        - ![c_labs_server](image.png)
    - **list command**
        - ![list_files](image-1.png)
    - **reading a file**
        - ![read_files](image-2.png)
    - **Performing 2 writes concurrently but latter one blocks**
        - ![2_write](image-3.png)
    - **Current writing client exits writing, now the blocked writer can perform write**
        - ![after_one_exit](image-4.png)
    - **deleting file**
        - ![delete](image-5.png)
    - **exit**
        - ![exit](image-6.png)