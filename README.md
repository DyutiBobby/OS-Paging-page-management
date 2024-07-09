# OS-CP: **PAGING AND PAGE MANAGEMENT**
## Authors - **Atharva Dusane(63), Dyuti Bobby(64)** [TY ETA ]
#

ASSUMPTIONS:
- Program loaded in secondary memory starting at location 00 
- Paging introduced, page table stored in real memory
- Program pages allocated one of 30 main memory blocks using random number generator 
- No multiprogramming, load and run one program at a time
- SI interrupt for service request
- PI interrupt for program errors introduced
- TI interrupt for time-out error introduced
- Time limit, line limit, out-of-data errors introduced

NOTATION: 
- mainMemory: Primary memory (300 lines)
- secMemory: Secondary memory (500 lines)
- IR: Instruction Register (4 bytes)
- IR [1, 2]: Bytes 1, 2 of IR/Operation Code
- IR [3, 4]: Bytes 3, 4 of IR/Operand Address 
- IC: Instruction Counter Register (2 bytes)
- reg: General Purpose Register (4 bytes)
- Toggle (1 byte)
- PTR: Page Table Register
- PCB: Process Control Block (data structure)
- VA: Virtual Address
- RA: Real Address
- TTC: Total Time Counter
- LLC: Line Limit Counter
- TTL: Total Time Limit
- TLL: Total Line Limit
- p_track: Program track
- no_pc: Number of program cards
- d_track: Data Track
- no_dc: Number of data cards
- EM: Error Message
- cards: 10 instructions are stored in 1 card
#
# Description
The program we have created is a simulation of a simple operating system that utilizes virtual memory.The input file is "Input.txt" and the secondary memory  has been stored to "MemoryOutput.txt". The functions are:

- mainMemoryPrint() - prints the content of the main memory to the console.
- secMemoryPrint() - prints the content of the secondary memory to a file.
- load() - resets the memory and related parameters to their default values.
- printPartMemory(int start) - prints a portion of the content of the main memory starting from the specified memory location.
- printPartSecMemory(int start) - prints a portion of the content of the secondary memory starting from the specified memory location.
- increment() - increments the instruction counter by one.
- terminate(int errorCode) - prints an error message based on the error code provided and updates the execution mode accordingly.
- readData(int memoryLocation) - reads data from the input file and stores it in the specified memory location in the main memory.
- writeData(int memoryLocation) - writes the content of the specified memory location in the main memory to the output file.
- loadReg(int memoryLocation) - loads the content of the specified memory location in the main memory into the accumulator register.
- storeReg(int memoryLocation) - stores the content of the accumulator register in the specified memory location in the main memory.
- compare(int memoryLocation) - compares the content of the specified memory location in the main memory with the content of the accumulator register.
- branch(int memoryLocation) - updates the instruction counter to the specified memory location in the main memory.
- MOS(int memoryLocation) - performs a machine-oriented operation based on the memory location provided.
- generateRandom() - generates a random number.
- getRealAddress(int virtualAddress) - converts a virtual memory address to a real memory address by fetching address from PTR.
- allocateMemory(int virtualAddress) - allocates memory for a page with the specified virtual address.
- checkPageFault(int virtualAddress) - checks if there is a page fault for the specified virtual address.

#


