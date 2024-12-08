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
        - ![c_labs_server](images/image.png)
    - **list command**
        - ![list_files](images/image-1.png)
    - **reading a file**
        - ![read_files](images/image-2.png)
    - **Performing 2 writes concurrently but latter one blocks**
        - ![2_write](images/image-3.png)
    - **Current writing client exits writing, now the blocked writer can perform write**
        - ![after_one_exit](images/image-4.png)
    - **deleting file**
        - ![delete](images/image-5.png)
    - **exit**
        - ![exit](images/image-6.png)
