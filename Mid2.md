### Chapter 10: Asymmetric-Key Cryptography

**1. Distinguish between symmetric-key and asymmetric-key cryptography.**
*   **Keys:** Symmetric uses a single **secret key** for both encryption and decryption. Asymmetric uses a **key pair**: a public key (for encryption) and a private key (for decryption).
*   **Security Services:** Symmetric is primarily used for **confidentiality** and high-speed bulk data encryption. Asymmetric provides **digital signatures** (non-repudiation) and secure **key exchange**.
*   **Key Distribution:** Symmetric faces the "key distribution problem" (how to share the secret key safely). Asymmetric simplifies this as the public key can be shared openly.

**2. Explain the "trapdoor one-way function" and its significance.**
*   A **one-way function** is easy to compute in one direction ($y = f(x)$) but computationally infeasible to reverse ($x = f^{-1}(y)$).
*   A **trapdoor** is special information that makes the reversal easy.
*   **Significance:** This is the mathematical basis of public-key cryptography. Anyone can encrypt (forward direction), but only the person with the trapdoor (the private key) can decrypt (reverse direction).

**3. Describe the RSA algorithm and the difficulty of integer factorization.**
*   **Process:** Select two large primes $p$ and $q$. Calculate $n = p \times q$. Choose an encryption key $e$ and calculate a decryption key $d$ such that $(e \times d) \equiv 1 \pmod{\phi(n)}$.
*   **Encryption:** $C = M^e \pmod n$; **Decryption:** $M = C^d \pmod n$.
*   **Security:** RSA's security relies on the fact that while multiplying two large primes is easy, **factoring** a very large number ($n$) into its original primes ($p$ and $q$) is currently impossible within a reasonable timeframe for 2048-bit keys or higher.

**4. Why is the public exponent $e$ often a small prime like 65537?**
*   **Efficiency:** A smaller $e$ reduces the number of multiplications required for modular exponentiation ($M^e \pmod n$), making encryption and signature verification significantly faster.
*   **Why 65537 ($2^{16} + 1$)?** It is a Fermat prime. In binary, it has only two '1's ($10000000000000001$), which allows for very fast calculation while being large enough to avoid certain simple mathematical attacks that affect $e=3$.

**5. What is the "chosen ciphertext attack" (CCA) against RSA, and how does padding mitigate it?**
*   **The Attack:** RSA is naturally **malleable**. An attacker can intercept a ciphertext $C$, multiply it by another value, and ask the victim to decrypt it. The result might reveal the original message $M$.
*   **Padding (OAEP):** Optimal Asymmetric Encryption Padding (OAEP) adds structured randomness to the plaintext before encryption. This ensures that even if the same message is sent twice, the ciphertext is different, and any modification to the ciphertext will result in an invalid decryption, preventing CCA.

**6. Explain Diffie-Hellman Key Exchange and its Man-in-the-Middle (MitM) vulnerability.**
*   **Process:** Two parties agree on a large prime $p$ and a generator $g$. They exchange $g^a \pmod p$ and $g^b \pmod p$ to arrive at a shared secret $K = g^{ab} \pmod p$.
*   **MitM Vulnerability:** Diffie-Hellman does not **authenticate** the parties. An attacker can intercept the exchange, establish two separate secrets (one with Alice and one with Bob), and transparently decrypt/re-encrypt their traffic.

**7. Define the Discrete Logarithm Problem (DLP) and list its cryptosystems.**
*   **Definition:** Given $y, g,$ and $p$, find $x$ such that $y = g^x \pmod p$. While calculating $y$ is easy, finding $x$ (the logarithm) is computationally "hard" for large primes.
*   **Cryptosystems:**
    *   Diffie-Hellman Key Exchange
    *   ElGamal Encryption
    *   Digital Signature Algorithm (DSA)
    *   Elliptic Curve Cryptography (ECC) variants.

**8. How does ElGamal encryption differ from RSA in terms of ciphertext expansion?**
*   **RSA:** The ciphertext is roughly the same size as the modulus $n$. It is a 1-to-1 mapping.
*   **ElGamal:** The ciphertext consists of a pair of values $(C_1, C_2)$. Therefore, the ciphertext is **twice the size** of the original plaintext block.
*   **Reason:** ElGamal uses a fresh random number for every encryption, making it "probabilistic," which provides better security but results in this $2\times$ expansion.



**9. Explain the concept of Elliptic Curve Cryptography (ECC). Why smaller key sizes?**
*   **Concept:** Instead of relying on the difficulty of factoring large numbers, ECC relies on the algebraic structure of elliptic curves over finite fields. The security is based on the **Elliptic Curve Discrete Logarithm Problem (ECDLP)**.
*   **Key Size:** ECC offers the same level of security as RSA but with much smaller keys. For example, a **256-bit ECC key** provides security equivalent to a **3072-bit RSA key**. This makes it ideal for mobile devices and smart cards with limited memory and processing power.

**10. Describe the algebraic structure of a group in the context of cryptography.**
*   A **group** is a set of elements combined with a binary operation (like addition or multiplication) that satisfies four properties:
    1.  **Closure:** The result of the operation is also in the set.
    2.  **Associativity:** $(a \cdot b) \cdot c = a \cdot (b \cdot c)$.
    3.  **Identity Element:** There exists an element $e$ such that $a \cdot e = a$.
    4.  **Inverses:** Every element has an inverse that results in the identity.
*   In cryptography, we use **Finite Cyclic Groups** because they allow us to perform operations that are easy to do but hard to reverse (like modular exponentiation).

**11. What is the difference between a public key and a digital certificate?**
*   **Public Key:** A raw mathematical value used to encrypt data or verify a signature. It does not contain information about the owner.
*   **Digital Certificate:** A digital document (like X.509) that **binds** a public key to a specific identity (person or organization).
*   **Authority:** Certificates are issued and digitally signed by a **Certificate Authority (CA)** to prove that the public key truly belongs to the claimed sender.

**12. Explain the process of RSA signature generation and verification.**
*   **Generation (Sender):** The sender creates a hash of the message, then "encrypts" the hash using their **private key**. This result is the digital signature.
*   **Verification (Receiver):** The receiver "decrypts" the signature using the sender's **public key** to get the original hash. They then hash the received message themselves. If the two hashes match, the signature is valid.
*   **Goal:** This ensures **integrity** (message wasn't changed) and **non-repudiation** (only the private key owner could have signed it).

**13. How does the "square-and-multiply" algorithm optimize modular exponentiation?**
*   Calculating $x^y \pmod n$ directly is slow if $y$ is very large.
*   **Optimization:** The algorithm converts the exponent $y$ into its binary form. It iterates through the bits:
    *   For every bit, you **square** the current result.
    *   If the bit is a **1**, you also **multiply** by the base $x$.
*   This reduces the number of multiplications from $y$ to approximately $\log_2(y)$, making RSA encryption significantly faster.

**14. Define the role of a Trusted Third Party (TTP) in asymmetric-key distribution.**
*   In a large network, users cannot manually exchange public keys with everyone.
*   A **TTP** (like a CA or a Key Distribution Center) acts as a middleman that everyone trusts. It verifies the identity of users and issues certificates.
*   When Alice wants Bob’s public key, she trusts the TTP's signature on Bob’s certificate, ensuring she isn't being tricked by an attacker.

**15. Contrast "Key Encapsulation Mechanisms" (KEM) with traditional public-key encryption.**
*   **Traditional Encryption:** You encrypt the actual message (or a part of it) using a public key. This can be slow and subject to padding attacks.
*   **KEM:** You use the public key to **encapsulate** (securely wrap) a randomly generated symmetric key.
*   **Hybrid approach:** Once the symmetric key is "encapsulated" and sent, both parties use that symmetric key (like AES) for the actual message. KEM is more efficient and is the standard for modern protocols like TLS 1.3 and Post-Quantum Cryptography.


<!-- chapter 11  -->

### Chapter 11: Message Integrity and Message Authentication

**1. Define message integrity. How does it differ from message confidentiality?**
*   **Integrity:** Ensures that the message has not been altered, tampered with, or corrupted during transit. It guarantees that "what was sent is what was received."
*   **Confidentiality:** Ensures that the message is kept secret from unauthorized parties. 
*   **Difference:** You can have integrity without confidentiality (e.g., a public announcement that everyone can read but no one can change) and confidentiality without integrity (e.g., an encrypted message that an attacker modifies, causing it to decrypt into garbage).

**2. What is a Modification Detection Code (MDC) and its use?**
*   An **MDC** is a message digest (hash) created from the message. 
*   **Use:** It is used to detect any change in the message. Because an MDC does not use a secret key, it must be sent through a **secure channel** (separate from the message) to prevent an attacker from changing both the message and the MDC.

**3. Explain Message Authentication Code (MAC). What does it provide over MDC?**
*   A **MAC** is a keyed hash function. It requires the message and a **shared secret key** as inputs.
*   **Advantage over MDC:** Unlike an MDC, a MAC can be sent over an insecure channel alongside the message. An attacker cannot forge a new MAC for a modified message because they do not possess the secret key. It provides both **integrity** and **data origin authentication**.

**4. Describe the process of generating a MAC using a secret key.**
1.  The sender takes the message ($M$) and a symmetric secret key ($K$).
2.  A MAC algorithm (like HMAC) is applied: $C = MAC(K, M)$.
3.  The sender sends $(M + C)$ to the receiver.
4.  The receiver, possessing the same key $K$, recalculates the MAC from the received message and compares it to the received $C$. If they match, the message is authentic.

**5. What is the "security through secrecy" fallacy in MAC design?**
*   This refers to the mistake of believing a MAC is secure just because the algorithm itself is kept secret. 
*   In modern cryptography, we follow **Kerckhoffs's Principle**: the security of the system should rely entirely on the secrecy of the **key**, not the secrecy of the algorithm. A strong MAC should remain secure even if the attacker knows exactly how the algorithm works.

**6. Explain the "Replay Attack" and how to prevent it.**
*   **The Attack:** An attacker captures a valid message and its MAC (e.g., a "Transfer $100" request) and sends it again later to the receiver. Since the MAC is valid, the receiver may process the request a second time.
*   **Prevention:**
    *   **Sequence Numbers:** Each message gets a unique incrementing number.
    *   **Timestamps:** Messages are only valid if received within a specific time window.
    *   **Nonces:** A unique "number used once" is exchanged for each session.

**7. Compare and contrast a MAC with a Digital Signature.**
*   **Key Type:** MAC uses a **symmetric key** (shared); Digital Signatures use **asymmetric keys** (private/public).
*   **Non-repudiation:** A MAC does **not** provide non-repudiation (since both parties have the key, either could have created the MAC). A Digital Signature **does** provide non-repudiation because only the sender has the private key.
*   **Efficiency:** MACs are computationally faster than digital signatures.

**8. Explain "Encrypt-then-MAC" vs "MAC-then-Encrypt".**
*   **MAC-then-Encrypt:** You calculate the MAC of the plaintext, append it, and then encrypt everything.
*   **Encrypt-then-MAC:** You encrypt the plaintext first, then calculate the MAC of the resulting ciphertext.
*   **Security:** **Encrypt-then-MAC** is generally considered the most secure because the receiver can check the MAC (integrity) and discard malicious packets before even attempting to perform the expensive decryption process.


**9. Explain the nested MAC construction. Why is it used?**
*   **Construction:** A nested MAC applies the hashing or MAC process in two stages (an inner and an outer stage) using different derived keys or constants.
*   **Why it's used:** It is primarily used to prevent **length-extension attacks**. In simple hashing, an attacker could potentially append data to a message and calculate a valid new hash. Nesting ensures that the output of the first stage is "wrapped" by a second stage, making it impossible to predict the final output by just knowing the intermediate result.

**10. Define the properties of a secure MAC algorithm.**
*   **Arbitrary-length input:** It should accept messages of any size.
*   **Fixed-length output:** It must produce a consistent, short tag (MAC).
*   **Key dependence:** The output must change completely if even one bit of the secret key is altered.
*   **Computation Resistance:** Even if an attacker sees many pairs of messages and their corresponding MACs, they should not be able to forge a MAC for a new message without knowing the key.

**11. What is the role of a "nonce" in authentication protocols?**
*   A **nonce** (Number used ONCE) is a unique, random value generated for a specific communication session.
*   **Role:** It ensures **freshness**. By including a nonce in a MAC or signature, the sender proves that the message is being generated *right now* and is not a recording of a previous session. This is the primary defense against replay attacks.

**12. Describe the "Challenge-Response" mechanism for entity authentication.**
*   **Process:** 
    1.  The Verifier sends a random "challenge" (often a nonce) to the Claimant.
    2.  The Claimant performs a cryptographic operation on that challenge using their secret key (e.g., hashing it with a secret or signing it).
    3.  The Claimant sends the "response" back.
    4.  The Verifier checks if the response is correct.
*   **Benefit:** The Claimant proves they possess the secret key without ever actually revealing the key itself over the network.

**13. How can symmetric-key cryptography be used to provide message authentication?**
*   Since both the sender and receiver share the same secret key, any message that can be successfully decrypted or verified with that key must have originated from someone who possesses it.
*   By using a keyed function like **CBC-MAC** (where the last block of a CBC-mode encryption is used as the tag), the parties ensure that the message was not modified and was sent by the legitimate key holder.

**14. Explain the difference between data origin authentication and entity authentication.**
*   **Data Origin Authentication:** Verifies that a specific *message* came from a certain source (e.g., "This email came from Bob"). It is "static" and linked to the data itself.
*   **Entity Authentication:** Verifies the *identity* of a person or device in real-time during a login or handshake (e.g., "The person currently trying to log in is indeed Bob"). This is "dynamic" and typically involves a challenge-response session.

**15. Discuss the limitations of MACs regarding non-repudiation.**
*   **The Limitation:** MACs use a **symmetric key** known by both the sender (Alice) and the receiver (Bob).
*   **The Problem:** If a dispute arises, Bob cannot prove to a judge that Alice sent the message. Alice can claim that Bob, also knowing the key, created the MAC himself to frame her. 
*   **Solution:** For true non-repudiation, one must use **Digital Signatures** (asymmetric cryptography), where only one person holds the private signing key.


### Chapter 12: Cryptographic Hash Functions

**1. Define a cryptographic hash function and its three primary security properties.**
A cryptographic hash function takes an arbitrary-sized input and produces a fixed-size output (digest). To be secure, it must satisfy:
*   **Pre-image Resistance:** Given a hash $h$, it should be computationally infeasible to find any input $x$ such that $H(x) = h$.
*   **Second Pre-image Resistance:** Given an input $x$, it should be impossible to find a different input $y$ such that $H(x) = H(y)$.
*   **Collision Resistance:** It should be impossible to find *any* two distinct inputs $x$ and $y$ that produce the same hash $H(x) = H(y)$.

**2. Explain "Pre-image Resistance" and its importance for password storage.**
Pre-image resistance is the "one-way" property. In password storage, systems do not store the actual password; they store the hash. When you log in, the system hashes your input and compares it to the stored hash. If an attacker steals the database, pre-image resistance ensures they cannot reverse the hashes back into usable passwords.

**3. What is "Second Pre-image Resistance" and how does it prevent forgery?**
This property ensures that if an attacker knows a specific message and its hash, they cannot create a different "fake" message that results in that same hash. Without this, an attacker could intercept a digital document (like a contract), create a fraudulent version, and claim the original signature/hash still applies to the fake one.

**4. Define "Collision Resistance" and the "Birthday Paradox."**
Collision resistance means no two different messages should result in the same hash. The **Birthday Paradox** shows that the probability of a collision is much higher than one might expect. In a group of just 23 people, there is a 50% chance two share a birthday. In cryptography, this means for a hash of size $n$, an attacker only needs to check approximately $2^{n/2}$ messages (rather than $2^n$) to find a collision.

**5. Describe the Merkle-Damgård construction.**
This is a method for building variable-length hash functions. 
*   The message is broken into fixed-size blocks.
*   The first block and an **Initialization Vector (IV)** are fed into a **compression function**.
*   The output of that function is then fed into the next compression function along with the second block.
*   This "chaining" continues until the final block, which produces the final hash digest.


**6. What is the "Iterated Hash Function" design?**
An iterated hash function uses a repeated process to handle long messages. It involves:
1.  **Preprocessing:** Padding the message so its length is a multiple of the block size.
2.  **Processing:** Using a compression function $f$ repeatedly on the blocks.
3.  **Finalization:** An optional step to transform the last internal state into the final digest.
Most modern hashes (MD5, SHA-1, SHA-2) are iterated hash functions.

**7. Explain the architecture of SHA-512.**
SHA-512 is a member of the SHA-2 family.
*   **Message Block Size:** 1024 bits.
*   **Word Size:** 64 bits (it operates on 8 words per round).
*   **Digest Size:** 512 bits.
*   **Rounds:** It performs 80 rounds of operations involving logical functions, constants, and modular addition to ensure high diffusion and confusion.

**8. How does padding in SHA-512 ensure the message length is included?**
SHA-512 padding ensures the total message length is a multiple of 1024. 
*   It appends a '1' bit, followed by enough '0' bits to reach 128 bits short of the multiple.
*   The **final 128 bits** are reserved to store the binary representation of the **original message length**. 
*   This "Length Padding" is a defense against attacks where an attacker might try to find messages of different lengths that hash to the same value.


**9. What is an HMAC? Why is $H(K || M)$ insecure?**
*   **HMAC (Hash-based Message Authentication Code):** A specific construction for calculating a MAC using a cryptographic hash function in combination with a secret key.
*   **The Insecurity:** Simple concatenation ($H(K || M)$) is vulnerable to **length-extension attacks**. If an attacker knows the hash of $M$, they can calculate the hash of $(M || \text{extra data})$ without knowing the secret key $K$. HMAC prevents this by using a nested structure: $H(K_{out} || H(K_{in} || M))$.

**10. Explain the "Length Extension Attack."**
*   This attack affects hash functions based on the Merkle-Damgård construction (like MD5, SHA-1, and SHA-2).
*   Because the hash output is simply the internal state of the algorithm after the last block, an attacker can use that output as a starting point to continue hashing additional data. This allows them to forge a valid hash for a longer message ($M + \text{attack data}$) without ever knowing the original message content or the secret key used in a prefix-MAC.

**11. Compare SHA-256 and SHA-512.**
| Feature | SHA-256 | SHA-512 |
| :--- | :--- | :--- |
| **Digest Size** | 256 bits | 512 bits |
| **Block Size** | 512 bits | 1024 bits |
| **Word Size** | 32 bits | 64 bits |
| **Number of Rounds** | 64 | 80 |
*   **Performance:** SHA-512 is often faster than SHA-256 on 64-bit processors because it processes more data per round using 64-bit native instructions.

**12. What is a "compression function" in hash algorithms?**
*   The compression function is the "engine" of an iterated hash function. 
*   It takes two inputs: the fixed-size data block from the message and the intermediate hash value (chaining variable) from the previous step. 
*   It "compresses" these into a single output of the same size as the intermediate hash value. This process ensures that every bit of the input influences the final digest.



**13. Discuss the security implications of collisions in MD5 and SHA-1.**
*   **MD5:** Now considered cryptographically broken. Collisions can be generated in seconds on a standard laptop. It should never be used for security-sensitive applications.
*   **SHA-1:** Also considered weak. Major browsers and certificate authorities have deprecated it because "collision attacks" (finding two different files with the same hash) have become computationally feasible for well-funded attackers.
*   **Result:** Use of these algorithms can lead to forged digital certificates or tampered software updates that appear "authentic."

**14. How are hash functions used in Digital Signatures?**
*   Signing a large message directly with asymmetric encryption is extremely slow and results in a huge signature.
*   **The Efficient Way:** 
    1.  The sender hashes the message to create a short, fixed-length digest.
    2.  The sender encrypts only that **digest** with their private key.
    3.  This encrypted digest is the signature.
*   This ensures the signature is small, fast to compute, and still uniquely tied to the entire content of the original message.

**15. Explain the concept of "Salt" and its defense against Rainbow Tables.**
*   **The Problem:** If two users have the same password (e.g., "Password123"), their hashes will be identical. Attackers use **Rainbow Tables** (pre-computed lists of hashes for common passwords) to crack them instantly.
*   **The Solution (Salt):** A "Salt" is a unique, random string added to the password *before* hashing ($H(\text{password} + \text{salt})$).
*   **Defense:** Even if two users have the same password, their hashes will be different because their salts are different. This makes Rainbow Tables useless, as the attacker would have to compute a new table for every possible salt value.