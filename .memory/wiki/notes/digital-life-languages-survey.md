# Architectures of Digital Life: A Comprehensive Survey of Languages for In Silico Code Evolution

> Source: Gemini share link `https://share.gemini.google/DVAThEEz6YzL` (extracted 2026-09-14). Faithful Markdown reproduction including the three comparison tables. The two source sections below ("Sources used" / "Sources read but not used") were recovered from the live Gemini conversation `https://gemini.google.com/app/a35957a414e98087`, which the share link omits; links are the original chip targets.

## 1. Introduction to Digital Evolution Architectures

The synthesis of artificial life within computational substrates necessitates a fundamental departure from traditional software engineering paradigms. In conventional computer science, programming languages are inherently brittle; they rely on strict syntactic rules and absolute memory addressing, meaning that a single random perturbation—a mutated byte or a flipped bit—invariably results in catastrophic failure, infinite loops, or system crashes. Conversely, biological evolution relies on a genetic code that is extraordinarily robust to mutation, allowing populations to explore vast phenotypic spaces through gradual complexification, genetic drift, and adaptation. To instantiate open-ended Darwinian evolution in silico, researchers must design specialized genetic programming languages and virtual execution environments wherein random alterations yield viable, executable code.

The evolution of these computational languages reveals a central tension in synthetic biology and artificial intelligence: the intrinsic trade-off between computational expressiveness, execution efficiency, and mutational robustness. Early models that relied on standard assembly languages proved excessively fragile, leading to population extinction rather than adaptation. Subsequent architectures introduced brilliant biological analogues, including unargumented instructions, template-based memory addressing, strict spatial isolation, stack-based type safety, and chemical computing paradigms. These innovations ensure that executing code remains functional—or at least non-destructive—regardless of its structural integrity following mutation, crossover, or deletion.

This report provides an exhaustive, narrative-driven survey of the programming languages and instruction sets developed for digital evolution. It analyzes their design specifications, operational intricacies, and respective theoretical advantages and limitations. Furthermore, this analysis evaluates these paradigms in the explicit context of Project Ouroborus—a distributed framework designed to simulate mobile agents operating on cellular automata backgrounds. The ultimate objective is to provide a definitive recommendation on whether Ouroborus should adopt an existing language as a drop-in replacement or continue the development of its unfinished, native evolutionary language.

## 2. The Brittleness of the Primordial Soup: Coreworld and Redcode

The earliest attempts to foster digital evolution occurred within the framework of Core War, a 1984 programming game in which human-designed algorithms competed for control of a virtual machine's memory space. The programs, known as warriors, were written in a simplified assembly language called Redcode. In the late 1980s, researchers including Steen Rasmussen introduced random mutations into the execution and self-replication commands of these Redcode programs, birthing the Coreworld system.

### 2.1 The Redcode Instruction Set

Redcode operates on a classic assembly architecture, utilizing operational codes (opcodes) followed by operands that dictate memory manipulation. The opcodes include standard data movement instructions such as MOV, arithmetic operations like ADD, SUB, MUL, and DIV, and control flow directives such as unconditional jumps (JMP) and conditional decrements (DJN). The operands utilize a complex variety of addressing modes, including immediate offsets, direct addressing, indirect addressing via primary and secondary offsets, as well as predecrement and postincrement operators.

Because code and data share a single, unified address space in the Coreworld virtual machine, self-modifying logic is not only possible but frequent, creating a highly volatile environment. Recent research utilizing Large Language Models (LLMs) in a framework known as Digital Red Queen (DRQ) has demonstrated that Redcode environments can support adversarial co-evolution. By utilizing LLMs to iteratively mutate and generate warriors that defeat previous generations, researchers observed convergent evolution toward generalized, robust strategies.

### 2.2 The Fragility of Argumented Assembly

Despite its computational completeness and recent utility in LLM-guided adversarial training, Redcode fundamentally fails as a substrate for unguided, autonomous in silico evolution due to its extreme mutational brittleness. The reliance on argumented instructions means that the opcodes and their corresponding operands are tightly coupled. An independent, random mutation to an instruction's argument is highly unlikely to produce a biologically meaningful or computationally stable combination.

In empirical tests evaluating Redcode within the context of self-replicating populations, researchers found that over 99.7 percent of all non-trivial mutations were strictly deleterious, resulting in immediate programmatic death. A single malfunctioning digital organism could write garbage data to the memory spaces of hundreds of neighboring programs before its own execution terminated, effectively bringing the entire population to extinction. The few mutations that did not crash the system were almost entirely neutral, and continuous evolutionary adaptation proved impossible without external guidance. This failure catalyzed the realization that biological evolution requires protected memory spaces and mutational safety mechanisms built directly into the instruction set.

| Architecture Feature | Redcode (Coreworld) Specification | Evolutionary Implication |
| --- | --- | --- |
| Instruction Format | Argumented (Opcode + Operand). | High fragility; mutated operands cause illegal memory access. |
| Addressing Scheme | Absolute and relative numeric addressing. | Jumps frequently land on invalid instructions after insertions/deletions. |
| Memory Isolation | Global shared memory; no write protection. | Parasitic cascades; malfunctioning organisms destroy neighbors. |
| Mutation Viability | >99.7% of mutations are deleterious. | Prevents open-ended evolution; populations quickly face extinction. |

## 3. The Biological Analogue: Tierra and Template Matching

Recognizing the fundamental limitations of standard assembly languages, evolutionary biologist Tom Ray engineered the Tierra system in 1990. Ray understood that biological systems do not rely on absolute Cartesian coordinates to locate resources or genes; rather, biomolecules interact based on topological affinity and chemical templates. Tierra translated this biological principle into a revolutionary virtual computer architecture designed specifically to harbor synthetic life.

### 3.1 The Tierran Virtual Machine and Instruction Set

The Tierran virtual computer is a parallel machine of the Multiple Instruction, Multiple Data (MIMD) type. Within this universe, Central Processing Unit (CPU) time represents the energetic resource, while Random Access Memory (RAM) represents the physical, spatial resource. Each digital organism is granted a virtual CPU that features an instruction pointer (IP) and generic registers, notably including the AX, BX, CX, and DX registers. These registers are utilized for localized memory manipulation, such as storing the organism's memory address in the BX register and its genomic size in the CX register.

The Tierran instruction set is characterized by its strict minimality and the complete absence of numeric operands. The alphabet consists of exactly 32 instructions, fitting precisely into a 5-bit sequence. To eliminate the brittleness of jump commands pointing to absolute memory addresses, Ray implemented an addressing architecture based on template matching.

Templates in Tierra are constructed from sequences of No-Operation instructions, specifically NOP_0 and NOP_1. When a digital organism executes a jump instruction, it is immediately followed by a specific NOP sequence, acting as a biological tag. The virtual CPU suspends sequential execution and searches outward—typically within a limit of 200 to 400 instructions—for the complementary NOP sequence. For example, if a jump is followed by the sequence NOP_0, NOP_0, NOP_1, the CPU searches for the complement NOP_1, NOP_1, NOP_0 and resumes execution at that locus.

### 3.2 Evolutionary Dynamics and Limitations

The unargumented, template-based architecture of Tierran assembly solved the brittleness problem. If a random bit-flip mutates a NOP_0 into a NOP_1, the template simply changes. The program searches for a different complement, potentially executing a different subroutine, but it does not crash. Furthermore, Tierra implemented memory allocation as a semi-permeable membrane. Organisms can read and execute instructions located in the memory spaces of other organisms, but they are strictly prohibited from writing to unallocated space.

This write-protection, combined with read-privileges, led to the spontaneous emergence of complex ecological interactions. The system natively evolved parasites that matched the templates of larger hosts, hijacking their replication code to reproduce faster. This was subsequently followed by the evolution of hyper-parasites and communal organisms. However, despite this initial explosion of diversity, Tierra ultimately struggles to achieve sustained open-ended evolution (OEE). Because all organisms exist in a single global memory space, they quickly exhaust the combinatorial possibilities of the simple environment. Analysis of long-term Tierran runs demonstrates that while the physical length of the organisms increases over millions of instructions executed, their actual phenotypic complexity plateaus. The environment lacks the geographic isolation and metabolic richness necessary to drive continuous complexification.

## 4. Spatial Topologies and Logic-Based Fitness: Avida

To address the ecological plateau observed in Tierra, a team led by Charles Ofria, Titus Brown, and Chris Adami developed the Avida platform in 1993. Avida retains the core biological principles of Tierran assembly but radically alters the topology of the environment and the selective pressures applied to the digital organisms, shifting the focus toward spatial dynamics and complex computational tasks.

### 4.1 Avidian Architecture and Phenotypic Computation

Unlike Tierra's global soup, Avida places organisms on a two-dimensional toroidal lattice. Each cell on the grid houses a maximum of one organism, and organisms can only interact with their immediate geographic neighbors. This rigid spatial structure prevents remote execution and naturally fosters speciation, as isolated pockets of the grid can evolve distinct genetic lineages without immediately being outcompeted by a global dominant strain.

The virtual CPU of an Avidian organism contains a circular genome composed of a 26-instruction alphabet. The hardware architecture includes the AX, BX, and CX registers, alongside two vital input buffers (input-1 and input-2) used to receive 32-bit binary numbers from the simulation environment. Furthermore, the CPU controls execution via multiple heads, including a read head, a write head, and a flow head, which dictate exactly where instructions are processed and copied during cellular division.

Avida introduces genuine phenotypic traits through a process of computational metabolism. The environment feeds randomized binary numbers into the organism's buffers, and the organism uses its instruction set to perform mathematical and logical operations on these numbers. Crucially, the genetic language of Avida contains only one explicit logic operator: the nand (Not-And) instruction. The nand command reads the contents of the BX and CX registers, performs a bitwise NAND operation, and stores the result.

To compute any other Boolean logic operation—such as NOT, AND, OR, XOR, or EQU (equals)—the organism must evolve complex, multi-step algorithms utilizing sequences of nand operations interspersed with data manipulation instructions. Once an operation is computed, the IO (Input-Output) instruction outputs the result. If the output matches a rewarded logic task (such as the Logic-77 task set), the environment grants the organism additional virtual CPU cycles, vastly accelerating its replication rate.

### 4.2 Environmental Adaptability and Genotype-Phenotype Mapping

The Avidian paradigm allows researchers to map out vast genotype-phenotype networks. Studies evaluating billions of viable sequences demonstrate that Avidian evolution navigates neutral networks—clusters of genotypes that share the same phenotype and can be traversed via neutral mutations. This allows populations to drift across the fitness landscape without losing functionality until they discover a beneficial mutation.

Furthermore, Avida has been heavily utilized to study adaptation in cyclically changing environments. By altering which Boolean logic tasks yield CPU cycles (e.g., simulating a day/night or seasonal cycle), populations in Avida evolve generalized phenotypic plasticity and robust memory management strategies to survive shifting resource availability. The strict grid layout and explicit environmental rewards make Avida unparalleled for studying eco-evolutionary dynamics, though the heavy bias toward integer manipulation and bitwise logic restricts its utility in simulating continuous physical environments.

| Feature | Tierran Paradigm | Avidian Paradigm |
| --- | --- | --- |
| Topology | 1D Global Memory Soup. | 2D Toroidal Lattice. |
| Interaction Scope | Global read-access; organisms can execute each other's code. | Localized spatial interaction; organisms are isolated to their grid cells. |
| Instruction Set Focus | 32 instructions, minimal, no direct logic tasks. | 26 instructions, heavily focused on nand logic and integer manipulation. |
| Selective Pressure | Implicit: Pure competition for raw CPU time and RAM space. | Explicit: Rewarded for computing Boolean logic tasks with extra CPU cycles. |

## 5. Stack-Based Generative Architectures: Push and Plush

While Tierran and Avidian languages simulate biological processes at an assembly-level analogue, the Push programming language, developed by Lee Spector, elevates artificial life into the realm of high-level program synthesis. Push was explicitly designed to support Genetic Programming (GP) without the syntax errors that typically plague tree-based representations, allowing algorithms to organically evolve multi-data-type operations and complex control flows.

### 5.1 The Push Architecture: Typed Stacks and Syntactic Minimality

The foundational innovation of the Push architecture is its multi-typed, stack-based execution model. Rather than relying on rigid syntax or memory registers, a Push interpreter maintains entirely separate data stacks for each operational type, including INTEGER, FLOAT, BOOLEAN, STRING, VECTOR, and CODE.

Execution flow is governed by a dedicated EXEC stack. The entire genome is initially pushed onto the EXEC stack. The interpreter operates in a continuous loop, popping the top item off the EXEC stack and evaluating it. If the item is a literal value (e.g., the integer 42), it is immediately pushed onto its respective data stack (the INTEGER stack). If the item is an instruction (e.g., INTEGER.ADD), it looks to the appropriate typed stacks for its arguments, executes the computation, and pushes the result back to the respective stack.

This architecture provides absolute mutational robustness through the concept of syntactic minimality, implemented via "NOOPing." Because arguments are drawn from typed stacks rather than fixed textual positions, an instruction can never encounter a type error. If an instruction is called but the required arguments are not present (for instance, executing FLOAT.DIVIDE when the float stack is empty), the instruction gracefully defaults to a No-Operation (NOOP). It has zero effect on the system state, and execution simply proceeds to the next item on the EXEC stack. Consequently, any random permutation, insertion, or deletion of Push instructions constitutes a valid, executable program.

### 5.2 Autoconstructive Evolution and Plush Genomes

The inclusion of the CODE and EXEC stacks grants Push programs the extraordinary ability to manipulate their own genetic structure during runtime. Programs can duplicate code blocks, alter execution order, and build recursive macros dynamically. This capability birthed the paradigm of Autoconstructive Evolution, wherein digital organisms are responsible not only for solving tasks but also for constructing their own offspring. In doing so, the programs evolve their own mechanisms of mutation and recombination, fundamentally shifting the evolutionary process from human-designed genetic operators to algorithmically discovered reproductive strategies.

To facilitate uniform genetic variation akin to biological crossover, the Push architecture was extended to support linear genomes, known as Plush. Traditional Push programs are deeply nested trees governed by parentheses. A Plush genome, conversely, is a flat, linear sequence of instructions. Epigenetic markers—such as the close marker—are attached to instructions within the Plush sequence, dictating where parentheses should be inserted when the flat sequence is translated into a hierarchical Push program prior to execution.

Implementations of this architecture, such as pyshgp in Python and Clojush in Clojure, have proven incredibly successful in program synthesis benchmarks, often outperforming or rivaling modern Large Language Models in generating algorithmic solutions. To prevent infinite loops caused by self-modification, the interpreter enforces strict runtime limitations, such as the EVALPUSH-LIMIT, which caps the maximum number of executions allowed in a single top-level call. While immensely expressive, the stack-based paradigm incurs significant computational overhead, as the continuous pushing and popping of diverse data types requires constant memory reallocation, making it orders of magnitude slower to evaluate per instruction than raw, unargumented assembly.

## 6. Graph-Based and Chemical Paradigms

Beyond the dominant assembly and stack-based models, several niche languages focus on simulating specific molecular or networked interactions.

### 6.1 Cartesian Genetic Programming (CGP) and MicroGP

Developed by Julian Miller, Cartesian Genetic Programming (CGP) eschews sequential instruction execution entirely, instead representing programs as directed acyclic graphs. The genotype in CGP is a fixed-length array of integers mapping out nodes (functions) and connectivity.

The defining feature of CGP is implicit genetic redundancy. While the genotype may dictate hundreds of nodes, the phenotype only comprises the subset of nodes actively connected to the final output. Mutations frequently target inactive nodes, resulting in neutral genetic drift. This neutrality allows the system to traverse flat areas of the fitness landscape and escape local optima without degrading current performance, making CGP highly effective for evolving image filters and robust control algorithms.

Operating in a similar vein of maintaining robustness over complex architectures, MicroGP utilizes a highly customized instruction library to enforce valid structural evolution over traditional, hardware-specific assembly languages, acting as an evolutionary supervisor rather than a natively robust language.

### 6.2 Chemical Rewriting and String-Based Protocells

Chemical computing models attempt to treat code execution as molecular collision and catalysis. The Fraglets language, originally designed for autonomous communication protocols, operates via string-rewriting. Tokens inside execution brackets dictate behaviors upon interaction; for instance, the sequence [match x fork nop x] actively seeks strings tagged with x, duplicates itself, and separates upon collision.

A more recent advancement is the String programming language, designed by Mohiul Islam, which serves as a Turing-complete mechanism to simulate the metabolic processes of protocells. In this model, String programs act as computational ribozymes enclosed within a simulated semi-permeable membrane. The execution of these ribozymes is managed by a stochastic Gillespie algorithm, linking the probability of code execution directly to chemical concentrations.

### 6.3 Parallel Genetic Networks: COSMOS and REPLiCa

Tim Taylor's COSMOS system introduces the REPLiCa language to simulate multicellular regulation and parallel execution. REPLiCa Abandons the traditional instruction pointer. Instead, blocks of code are guarded by precondition expressions built from tags.

Execution relies on a central "tag store." An organism's tag block only triggers if the environmental tag store contains the requisite chemical concentrations matching its precondition expression (e.g., verifying the presence of ^tag 0 while ignoring wildcards like ^tag #). As code blocks execute, they utilize commands like ts create and ts destroy to modulate tag concentrations, organically forming complex promoter and repressor networks analogous to biological gene regulation.

### 6.4 Genome Architecture Simulation: Aevol

Aevol diverges entirely from agent-based task execution, focusing strictly on the macroscopic evolution of genomic architecture. Genomes in Aevol are treated as double-stranded nucleotide sequences. Instead of executing opcodes, the simulation performs in silico transcription and translation.

The resultant proteins are modeled mathematically as fuzzy sets. The overarching phenotype is calculated by aggregating these functional proteins and comparing them to a mathematical curve defined by the environment. This abstraction allows researchers to study the evolutionary pressures governing genome streamlining, non-coding DNA accumulation, and chromosomal rearrangements independent of algorithmic task-solving.

## 7. Architectural Context: Project Ouroborus

Project Ouroborus is a highly ambitious artificial life framework designed to simulate mobile computational agents residing atop a dynamic cellular automata (CA) background. Built as an educational and research tool for population genetics and ecology, the project aims to transcend isolated simulation environments by establishing a decentralized, peer-to-peer (P2P) network, fostering massive, semi-stable environmental persistence.

### 7.1 Framework Specifications and Implementation

The Ouroborus architecture is explicitly dual-layered. The abiotic layer is governed by a cellular automaton engine responsible for managing physics, spatial states, and energy resource flows. Operating on top of this CA grid are mobile agents that must possess the cognitive algorithms required to sense resources, navigate the grid, manage internal energy reserves, and execute reproductive functions.

From an implementation perspective, the project utilizes a multifaceted software stack. The underlying CA engine underwent multiple iterations to resolve performance bottlenecks. Originally written in Python, the engine was reimplemented in Pyrex (as a module named Birdcage), yielding a hundredfold increase in execution speed. Subsequently, an effort to port the engine entirely to Linux-compatible C++ (Cage Cpp) was initiated to maximize raw throughput. The framework further incorporates peripheral interfaces, including a curses terminal view, live audio synthesis via Csound, and experimental environmental input ingested from Arduino photosensors. Previous networking attempts included XML-RPC protocols (Yogiserver and Yogiclient) to manage the decentralized storage of digital organisms.

### 7.2 The Language Void

A critical deficiency in the Ouroborus project remains the genetic programming language intended to control the mobile agents. The native language designed for the framework was never completed, halting the instantiation of the evolutionary simulation. Therefore, the framework requires a drop-in replacement language. This language must be capable of processing sensory input from a 2D grid, managing complex movement vectors, and surviving continuous mutational processes, all while integrating seamlessly into a Python/C++ backend architecture.

## 8. Comparative Evaluation for Ouroborus Integration

To determine the most viable evolutionary language for Ouroborus, the candidates must be evaluated against the project's strict requirements: spatial awareness, data-type flexibility, and computational efficiency at massive scale.

| Candidate Language | Expressiveness & Data Types | Robustness Mechanism | Ouroborus CA Integration Compatibility | Computational Overhead |
| --- | --- | --- | --- | --- |
| Avidian (Avida) | Low. Bound to bitwise logic and integer registers. | Constrained architecture and spatial isolation. | High. Grid-based spatial paradigm aligns perfectly with CA environments. | Minimal. Registers map directly to C++ primitives. |
| Plush (PushGP) | Very High. Native support for floats, vectors, strings. | Absolute safety via stack-typing and NOOPing. | Medium. Requires building custom Push instructions for CA interaction. | Very High. Constant stack manipulation and execution limits bottleneck speed. |
| CGP | High for signal processing and control. | Neutral drift via inactive node redundancy. | Low. Cannot easily support self-modification or autonomous replication routines. | Low. Graph reduces easily to compiled active nodes. |
| Native Tierran Hybrid | Medium. Unargumented assembly tailored strictly to CA rules. | Template matching and restricted opcodes. | Perfect. Designed explicitly for the host environment. | Minimal. Highly optimized execution loop inside C++ core. |

### 8.1 The Case for Avidian Integration

Avida's architecture translates effectively to the spatial requirements of Ouroborus. Because Avida was built for a toroidal lattice, its conceptual design already accommodates local neighborhood interactions and resource mapping. A minimal Avidian virtual CPU is trivial to implement within the Cage Cpp backend. However, its instruction set is overwhelmingly biased toward bitwise logic. Forcing mobile agents to calculate 2D Euclidean distances or manage continuous energy gradients using iterative nand operations would severely stunt phenotypic evolution, resulting in agents that struggle to evolve beyond rudimentary locomotion.

### 8.2 The Case for Plush Integration

Plush represents the apex of expressive, biologically inspired program synthesis. Python implementations (pyshgp) already exist and could interface natively with the Python/Pyrex layers of Ouroborus. Plush handles floating-point mathematics, vectors, and complex conditional statements natively via its typed stacks. Creating Ouroborus agents in Plush simply requires adding custom instructions (e.g., CA.READ_CELL, AGENT.MOVE_FORWARD) to the interpreter. The NOOP behavior ensures that no matter how chaotic the mutation, the agent will never crash the simulation. Furthermore, its capacity for autoconstructive evolution aligns perfectly with the Ouroborus goal of open-ended adaptation.

## 9. Strategic Recommendations and Conclusion

The ultimate decision regarding the language architecture for Project Ouroborus hinges on a fundamental divergence in ALife simulation philosophy: Evolutionary Expressiveness versus Computational Scale.

**Recommendation 1: Adopt Plush (PushGP) to Maximize Expressiveness**

If the primary objective of Ouroborus is to achieve emergent, highly complex, open-ended evolution where agents invent unpredictable behaviors and reproductive strategies, Plush is the definitive drop-in replacement. The integration of a linear Push genome provides absolute mutational safety while accommodating the complex mathematics (floats, vectors) required to navigate a continuous or detailed CA grid. The trade-off is computational execution time; evaluating multi-typed stacks via an interpreter imposes severe overhead, which will limit the total population size that a single node in the P2P network can sustain in real-time.

**Recommendation 2: Finish the Native Language to Maximize Scale**

If extreme scale and raw simulation speed are the paramount objectives—allowing the decentralized network to host millions of concurrent, rapidly evolving entities—finishing the native Ouroborus language is the optimal path. The overhead of a Push interpreter may bottleneck the highly optimized Birdcage and Cage Cpp engines. By designing a custom, unargumented language that borrows Tierra's template-matching for robustness and Avida's spatial awareness for grid interaction, the developers can hard-code the execution loop directly into C++. This ensures cache efficiency and massive parallel execution, albeit at the cost of limiting the agents to simpler behavioral logic.

**Conclusion**

The trajectory of in silico evolutionary languages demonstrates a profound iterative refinement. The field progressed from the chaotic, fatal fragility of Redcode to the elegant biological mimicry of Tierra, the spatial rigor of Avida, and the generative, multi-typed power of Push. Each paradigm engineered a unique solution to the central problem of mutational robustness—via template matching, restricted instruction sets, and stack-based NOOPing. For modern synthetic environments like Project Ouroborus, prioritizing this mutational safety alongside appropriate data-type manipulation remains the definitive blueprint for synthesizing artificial complexity, ensuring that digital organisms can endlessly navigate the precipice of open-ended evolution.

## Sources used in the report

- [Project Ouroborus - Introduction](http://ouroborus.info/)
- [Digital Red Queen: Adversarial Program Evolution in Core War with](https://new.foundation/researchpapers/2601.03335v1.pdf)
- [Symbiosis in Digital Evolution: Past, Present, and Future - Frontiers](https://www.frontiersin.org/journals/ecology-and-evolution/articles/10.3389/fevo.2021.739047/full)
- [Adversarial Program Evolution in Core War with LLMs - arXiv](https://arxiv.org/html/2601.03335v1)
- [Genome of a digital organism and its virtual CPU, with registers,](https://www.researchgate.net/figure/Genome-of-a-digital-organism-and-its-virtual-CPU-with-registers-buffers-and-stack_fig1_3418708)
- [(PDF) Design of evolvable computer languages - ResearchGate](https://www.researchgate.net/publication/3418708_Design_of_Evolvable_Computer_Languages)
- [Digital Darwinism; Synthetic organisms evolve spontaneously... (Win](https://www1.udel.edu/PR/Messenger/92/2/16.html)
- [Evolution, Ecology and Optimization of Digital Organisms](https://faculty.cc.gatech.edu/~turk/bio_sim/articles/tierra_thomas_ray.pdf)
- [An Approach to the Synthesis of Life - Tom Ray](https://tomray.me/pubs/alife2/Ray1991AnApproachToTheSynthesisOfLife.pdf)
- [Evolvability Tradeoffs in Emergent Digital Replicators - arXiv](https://arxiv.org/pdf/1511.07959)
- [Documentation for the Tierra Simulator - Tom Ray](https://tomray.me/pubs/doc/index.html)
- [(PDF) OPEN-ENDED ARTIFICIAL EVOLUTION - ResearchGate](https://www.researchgate.net/publication/220606221_OPEN-ENDED_ARTIFICIAL_EVOLUTION)
- [Cyberfeminism and Artificial Life | Uberty](https://uberty.org/wp-content/uploads/2015/09/Cyberfeminism-and-Artificial-Life-Sarah-Kember.pdf)
- [Avida: A Software Platform for Research in Computational](https://www.cse.msu.edu/~ofria/pubs/2009AvidaIntro.pdf)
- [From Simulated Worlds to Infrastructural Ecologies](https://alife-in-the-wild.github.io/artificial-life-in-the-wild.pdf)
- [Requirements for Open-Ended Evolution in Natural and Artificial](https://arxiv.org/html/1507.07403v1)
- [Requirements for Open-Ended Evolution in Natural and Artificial](https://www.researchgate.net/publication/280445471_Requirements_for_Open-Ended_Evolution_in_Natural_and_Artificial_Systems)
- [Evolutionary Learning in the 2D Artificial Life System "Avida"](https://www.researchgate.net/publication/2726976_Evolutionary_Learning_in_the_2D_Artificial_Life_System_Avida)
- [Fluctuating environments select for short-term phenotypic variation](https://journals.plos.org/ploscompbiol/article?id=10.1371/journal.pcbi.1006445)
- [Digital Evolution for Ecology Research: A Review - Frontiers](https://www.frontiersin.org/journals/ecology-and-evolution/articles/10.3389/fevo.2021.750779/full)
- [The genotype-phenotype map of an evolving digital organism](https://journals.plos.org/ploscompbiol/article?id=10.1371/journal.pcbi.1005414)
- [Autoconstructive Evolution: Push, PushGP, and Pushpop - Faculty](https://faculty.hampshire.edu/lspector/ACE-GECCO.pdf)
- [Tag-Based Modules in Genetic Programming - Research](https://groups.csail.mit.edu/EVO-DesignOpt/gecco2011Proceedings/proceedings/p1419.pdf)
- [Expressive Genetic Programming - Faculty](https://faculty.hampshire.edu/lspector/temp/spector-tutorial-gecco2015-1up.pdf)
- [Push 3.0 Programming Language Description - Faculty](http://faculty.hampshire.edu/lspector/push3-description.html)
- [Introduction To Push - ERP](https://erp12.github.io/push-redux/pages/intro_to_push/)
- [Recent Developments in Program Synthesis with Evolutionary](https://arxiv.org/html/2108.12227v1)
- [PushGP in Python - PyshGP - CMAP](http://www.cmap.polytechnique.fr/~nikolaus.hansen/proceedings/2017/GECCO/companion/companion_files/wksp212s1-file1.pdf)
- [(PDF) PyshGP: PushGP in Python - ResearchGate](https://www.researchgate.net/publication/318377320_PyshGP_PushGP_in_Python)
- [Evolution Evolves with Autoconstruction - Computer Science](https://www.cs.hamilton.edu/~thelmuth/Pubs/2016-GECCO-workshop-autoconstruction.pdf)
- [Work in Progress on Autoconstructive Evolution - Faculty](https://faculty.hampshire.edu/lspector/temp/META-2016.pdf)
- [Recent developments in autoconstructive evolution - ResearchGate](https://www.researchgate.net/publication/318375572_Recent_developments_in_autoconstructive_evolution)
- [Program Synthesis using Uniform Mutation by Addition and Deletion](http://www.cmap.polytechnique.fr/~nikolaus.hansen/proceedings/2018/GECCO/proceedings/proceedings_files/pap543s3-file1.pdf)
- [GitHub - lspector/Clojush: The Push programming language and the](https://github.com/lspector/Clojush)
- [A Comprehensive Survey on Program Synthesis With Evolutionary](https://www.researchgate.net/publication/359492604_A_Comprehensive_Survey_on_Program_Synthesis_with_Evolutionary_Algorithms)
- [GECCO 2013 tutorial: Cartesian genetic programming - ResearchGate](https://www.researchgate.net/publication/262408867_GECCO_2013_tutorial_Cartesian_genetic_programming)
- [[PDF] Cartesian Genetic Programming | Semantic Scholar](https://www.semanticscholar.org/paper/Cartesian-Genetic-Programming-Miller-Thomson/ccd109d92845b9d97ec123f940a04021f63d25a6)
- [(PDF) Neutral genetic drift: an investigation using Cartesian Genetic](https://www.researchgate.net/publication/276509430_Neutral_genetic_drift_an_investigation_using_Cartesian_Genetic_Programming)
- [Smoothness, Ruggedness and Neutrality of Fitness Landscapes](https://www.researchgate.net/publication/227056903_Smoothness_Ruggedness_and_Neutrality_of_Fitness_Landscapes_from_Theory_to_Application)
- [Crossover and Mutation Genetic Operators - ResearchGate](https://www.researchgate.net/figure/Crossover-and-Mutation-Genetic-Operators_fig1_221471866)
- [Genetic programming - Wikipedia](https://en.wikipedia.org/wiki/Genetic_programming)
- [Self-Replicating and Self-Modifying Programs in Fraglets](https://www.researchgate.net/publication/4369014_Self-Replicating_and_Self-Modifying_Programs_in_Fraglets)
- [String: A novel programming language with applications to genetic](https://spectrum.library.concordia.ca/id/eprint/995710/)
- [The COSMOS Environment and REPLiCa Programming Language](https://www.tim-taylor.com/papers/taylor1996cosmos.pdf)
- [From Artificial Evolution to Artificial Life - Tim Taylor](http://archive.tim-taylor.com/papers/thesis/html/main.html)
- [Aevol-9: A simulation platform to decipher the evolution of genome](https://www.biorxiv.org/content/10.1101/2025.04.10.648095v1.full-text)
- [Aevol 4b: Bridging the gap between artificial life and bioinformatics](https://direct.mit.edu/isal/proceedings-pdf/isal2024/36/6/2461181/isal_a_00716.pdf)
- [Modeling Evolution of Regulatory Networks in Artificial Organisms](https://pubs.aip.org/aip/acp/article-pdf/940/1/87/11882184/87_1_online.pdf)
- [The Aevol model. Genomes (A) contain genes decoded into proteins.](https://www.researchgate.net/figure/The-Aevol-model-Genomes-A-contain-genes-decoded-into-proteins-Functional-levels_fig2_349236296)
- [Aevol - Artificial Life](https://alife.org/encyclopedia/software-platforms/aevol/)
- [In silico experimental evolution: a tool to test evolutionary scenarios](https://pmc.ncbi.nlm.nih.gov/articles/PMC3851946/)
- [Agent-based Modeling - Complexity Sciences Center](https://csc.ucdavis.edu/~chaos/courses/nlp/Projects2008/AdamGetchell/AgentBasedModeling.phy250.Presentation.pdf)
- [JGEA: a modular java framework for experimenting with evolutionary](https://www.researchgate.net/publication/362115401_JGEA_a_modular_java_framework_for_experimenting_with_evolutionary_computation)

## Sources read but not used in the report

- [2D artificial life system using network-type assembly-like language](https://www.researchgate.net/publication/225323354_2D_artificial_life_system_using_network-type_assembly-like_language_influence_of_change_in_environment_with_costs_of_instructions)
- [The Surprising Creativity of Digital Evolution](https://d-nb.info/1281948519/34)
- [ARTIFICIAL INTELLIGENCE](https://ifotechpoly.edu.ng/elibrary/elibrary/computer_hardware_engineering/Artificial%20Intelligence%20A%20Systems.pdf)
- [Artificial Life 13 - MIT Press Direct](https://direct.mit.edu/isal/proceedings-pdf/alife2012/24/45/1901082/978-0-262-31050-5-ch007.pdf)
- [Tapes Together Strong: The Co-evolution of Computation ... - arXiv](https://arxiv.org/html/2609.10817v1)
- [Systematic Review (Up to 31 January 2025) on the Applications of](https://actascientific.com/ASMI/pdf/ASMI-08-1539.pdf)
- [On the Incorporation of a Developmental Process in a System of Self](https://www.tim-taylor.com/papers/taylor1996incorporation.pdf)
- [Ecological and Mutation-Order Speciation in Digital Organisms](https://www.journals.uchicago.edu/doi/full/10.1086/674359)
- [Adaptive phenotypic plasticity stabilizes evolution in fluctuating](https://www.biorxiv.org/content/10.1101/2021.05.25.445672v1.full-text)
- [Adaptive Phenotypic Plasticity Stabilizes Evolution in Fluctuating](https://www.frontiersin.org/journals/ecology-and-evolution/articles/10.3389/fevo.2021.715381/full)
- [Imitation of Life: Advanced system for native Artificial Evolution](https://www.intellectualarchive.com/getfile.php?file=NkenKOH9JFt&orig_file=Thomas_Sperl__Imitation_of_Life.pdf)
- [Origin of life in a digital microcosm - Royal Society Publishing](https://royalsocietypublishing.org/rsta/article/375/2109/20160350/58820/Origin-of-life-in-a-digital-microcosmOrigin-of)
- [Evolution takes multiple paths to evolvability when facing ... - PNAS](https://www.pnas.org/doi/10.1073/pnas.2413930121)
- [Apilar: An Alife System - Secret Weblog](https://blog.startifact.com/posts/apilar-an-alife-system/)
- [Self-modifying code - Wikipedia](https://en.wikipedia.org/wiki/Self-modifying_code)
- [Effective Adaptive Mutation Rates for Program Synthesis - arXiv](https://arxiv.org/html/2406.15976v1)
- [Code Building Genetic Programming - arXiv](https://arxiv.org/html/2008.03649v1)
- [Autoconstructive Evolution: Push, PushGP, and Pushpop - Faculty](https://faculty.hampshire.edu/lspector/pubs/ace.pdf)
- [Program Synthesis using Uniform Mutation by Addition and Deletion](https://www.cs.hamilton.edu/~thelmuth/Pubs/2018-GECCO-UMAD.pdf)
- [¿Piensan los hispanos que los acentos españoles suenan ... - Quora](https://es.quora.com/Piensan-los-hispanos-que-los-acentos-espa%C3%B1oles-suenan-elegantes-de-la-misma-manera-que-los-estadounidenses-piensan-que-los-acentos-ingleses-suenan-elegantes)
- [Lexicografía de oficios peruanos 1938-2015 | PDF | Palabra - Scribd](https://es.scribd.com/document/479817726/BOLETIN-DE-LA-LENGUA-27-51-PB)
- [Bedau: Philosophical Content and Method in Artificial Life](https://people.reed.edu/~mab/papers/digital.phoenix.htm)
- [A Survey of Irreducible Complexity in Computer Simulations](https://bio-complexity.org/ojs/index.php/main/article/viewfile/bio-c.2014.1/bio-c.2014.1)
- [open-ended-artificial-evolution.pdf](https://promathmedia.wordpress.com/wp-content/uploads/2013/02/open-ended-artificial-evolution.pdf)
- [(PDF) Avida: A Software Platform for Research in Computational](https://www.researchgate.net/publication/232808314_Avida_A_Software_Platform_for_Research_in_Computational_Evolutionary_Biology)
- [A Complete Bibliography of Publications in Communications of the](https://ftp.math.utah.edu/pub/tex/bib/cacm2020.pdf)
- [building cyberinfrastructure, interoperating the geosciences](https://escholarship.org/uc/item/2gf7b45n)
- [Publications - Tim Taylor](https://www.tim-taylor.com/publications/)
- [Tim Taylor's publications](http://archive.tim-taylor.com/research/publications_by_date.html)
- [Life, Information, Entropy, and Time: Vehicles for Semantic Inheritance](https://pmc.ncbi.nlm.nih.gov/articles/PMC2577055/)
- [Environmental bias forces parasitism in Tierra - MIT Press Direct](https://direct.mit.edu/isal/proceedings-pdf/ecal2015/27/294/1903783/978-0-262-33027-5-ch055.pdf)
- [N83- 15352 - NASA Technical Reports Server](https://ntrs.nasa.gov/api/citations/19830007081/downloads/19830007081.pdf?attachment=true)
- [Volume 12 Issue 5+6 2024 - COSMOS + TAXIS](https://cosmosandtaxis.org/wp-content/uploads/2024/05/ct_vol12_iss_5_6_epub.pdf)
- [(PDF) Viral evolution in the cosmos - ResearchGate](https://www.researchgate.net/publication/397333163_Viral_evolution_in_the_cosmos)
- [Defining Life: Conference Proceedings - Eduscol](https://eduscol.education.gouv.fr/sites/default/files/document/jeangayon2292522pdf-79848.pdf)
- [Global Optimization Algorithms and their Application to Distributed](https://kobra.uni-kassel.de/bitstreams/f4f6cba8-8c21-400b-9a37-e75a76156f5d/download)
- [Evolving Distributed Algorithms with Genetic ... - Kobra Uni Kassel](https://kobra.uni-kassel.de/bitstreams/cdce3bc4-548a-4cd4-b04f-646a2a7b3ea4/download)
- [Model Purpose and Overview - Aevol](https://www.aevol.fr/model-description/purpose-and-overview)
- [Detailed Model Description | Aevol](https://www.aevol.fr/model-description/detailed)
- [Using CoSMoS to Reverse Engineer a Domain Model for Aevol](https://www-users.york.ac.uk/~ss44/bib/ss/nonstd/cosmos14-aevol.pdf)
- [Innovation in viruses: fitness valley crossing, neutral landscapes, or](https://academic.oup.com/ve/article/10/1/veae078/7762305)
- [PSB2: The Second Program Synthesis Benchmark Suite | alphaXiv](https://www.alphaxiv.org/abs/2106.06086)
- [PSB2: The Second Program Synthesis Benchmark Suite](https://www.researchgate.net/publication/352373731_PSB2_The_Second_Program_Synthesis_Benchmark_Suite)
- [Google Sports Data](https://support.google.com/knowledgepanel/answer/9787176)
- [The Evolution of Biological Information - dokumen.pub](https://dokumen.pub/the-evolution-of-biological-information-how-evolution-creates-complexity-from-viruses-to-brains-0691241155-9780691241159.html)
- [Design and Information in Biology - MINAMS](https://www.minams.edu.pk/cPanel/ebooks/miscellaneous/Design+and+Information+in+Biology.pdf)
- [Core Wars Genetics: The Evolution of Predation - KOTH.org](http://www.koth.org/info/evolving_warriors.html)
- [Symbiosis in Digital Evolution: Past, Present, and Future](https://www.researchgate.net/publication/355947610_Symbiosis_in_Digital_Evolution_Past_Present_and_Future)
- [The Holland Broadcast Language and the Modeling of Biochemical](https://www.researchgate.net/publication/29652383_The_Holland_Broadcast_Language_and_the_Modeling_of_Biochemical_Networks)
- [Computational Complexity Analysis of Genetic Programming - arXiv](https://arxiv.org/html/1811.04465v2)
- [GP and LLMs for Program Synthesis: No Clear Winners - arXiv](https://arxiv.org/pdf/2508.03966)
- [String: A novel programming language with applications to genetic](https://spectrum.library.concordia.ca/995710/1/Islam_PhD_F2025.pdf)
- [PhD Oral Exam - Mohiul Islam, Electrical and Computer Engineering](https://www.concordia.ca/cuevents/offices/vprgs/sgs/2025/05/30/phd-oral-exam-mohiul-islam-electrical-and-computer-engineering.html)
- [Items where Author is "Islam, Mohiul" - Concordia's Spectrum](https://spectrum.library.concordia.ca/view/creators/Islam=3AMohiul=3A=3A.html)
- [‪Mohiul Islam - ‪Google Scholar](https://scholar.google.com/citations?user=usiCakIAAAAJ&hl=en)
- [Spectrum Research Repository - Concordia University](https://spectrum.library.concordia.ca/view/document_subtype/thesis=5Fphd/2025.html)
- [2025 - Spectrum Research Repository - Concordia University](https://spectrum.library.concordia.ca/view/doctype/thesis/2025.html)
- [Towards Advanced Phenotypic Mutations in Cartesian Genetic](https://www.researchgate.net/publication/323845977_Towards_Advanced_Phenotypic_Mutations_in_Cartesian_Genetic_Programming)
- [A Genetic Programming Approach to Designing Convolutional](https://arxiv.org/html/1704.00764v2)
- [An Exploration of Tree-Adjoining Grammars for Grammatical Evolution](http://ncra.ucd.ie/papers/EoinMurphy_thesis.pdf)
- [Evolving comprehensible and scalable solvers using CGP for](https://etheses.whiterose.ac.uk/id/eprint/19011/1/finalThesisv3.pdf)
- [Finding Needles in Haystacks Is Not Hard with Neutrality](https://neuro.bstu.by/ai/Data-mining/Ant/needle-is-easy.pdf)
- [Theory of randomized search heuristics in combinatorial optimization](https://scispace.com/pdf/theory-of-randomized-search-heuristics-in-combinatorial-3z5ogkazoy.pdf)
- [Corel Ventura - GEC02_PO.CHP - UCL Computer Science](http://www0.cs.ucl.ac.uk/staff/W.Langdon/ftp/papers/gecco2002/gecco-2002-14.pdf)
- [(PDF) 2019 Evolutionary Algorithms Review - ResearchGate](https://www.researchgate.net/publication/333971914_2019_Evolutionary_Algorithms_Review)
- [Agent based modeling-presentation | PDF - Slideshare](https://pt.slideshare.net/slideshow/agent-based-modelingpresentation/27088625?nway-refresh=B)
- [(PDF) A Genetic Source-Code Program-Synthesizer for Real-Time](https://www.researchgate.net/publication/400693831_A_Genetic_Source-Code_Program-Synthesizer_for_Real-Time_Co-Evolution_with_Humans_Gene-Level_Geometric-Push_Program-Synthesis)
- [2019 Evolutionary Algorithms Review - arXiv](https://arxiv.org/pdf/1906.08870)
- [GECCO '24 Companion: Proceedings of the Genetic and ... - sigevo](http://www.sigevo.org/gecco-2024/toc-companion.html)
- [GECCO 2024: Melbourne, VIC, Australia - DBLP](https://dblp.org/db/conf/gecco/gecco2024c)
- [Guideless Artificial Life Model for Reproduction, Development, and](https://direct.mit.edu/artl/article/31/1/31/127798/Guideless-Artificial-Life-Model-for-Reproduction)
- [(PDF) Avida: A Software Platform for Research in Computational](https://www.researchgate.net/publication/8598395_Avida_A_Software_Platform_for_Research_in_Computational_Evolutionary_Biology)
- [A Comparative Analysis on Introduction to Multicellular Organisms](https://www.ignited.in/index.php/jast/article/view/1109/2051)
- [AGI - Rigene Project](https://www.rigeneproject.org/tina-technical-intelligent-nervous-adaptive-system/agi)
- [Artificial Life - Martin Pilát](https://martinpilat.com/en/nature-inspired-algorithms/artificial-life)
- [Characterizing Open-Ended Evolution Through Undecidability](https://arxiv.org/html/2512.15534v4)
- [Evolvable AI: Threats of a new major transition in evolution | PNAS](https://www.pnas.org/doi/10.1073/pnas.2527700123)
- [Research on survival strategies of artificial life in dynamic environment](https://periodicals.karazin.ua/mia/article/download/27646/24401/)
- [The Stacked Autoencoder Evolution Hypothesis - arXiv](https://arxiv.org/html/2602.01026v1)
- [Programmable Cellular Automata - arXiv](https://arxiv.org/html/2609.06102v1)
- [Automating the Search for Artificial Life with Foundation Models - arXiv](https://arxiv.org/html/2412.17799v1)
- [Software for Agent-Based Computational Economics and Complex](https://faculty.sites.iastate.edu/tesfatsi/archive/tesfatsi/acecode.htm)
- [Self-Organising Applications: A Survey - SciSpace](https://scispace.com/pdf/self-organising-applications-a-survey-35act8cbd8.pdf)
- [WebAL Comes of Age: A Review of the First 21 Years of Artificial Life](https://meclab.w3.uvm.edu/papers/2016_ALife_Taylor.pdf)
- [Push 3.0 Programming Language Descripton - Faculty](https://faculty.hampshire.edu/lspector/temp/HC-CSTR-2004-02.pdf)
- [Lee Spector - Amherst College](https://www.amherst.edu/system/files/spector-cv-20250104.pdf)
- [PSB2: The Second Program Synthesis Benchmark Suite - arXiv](https://arxiv.org/pdf/2106.06086)
- [The Surprising Creativity of Digital Evolution](https://www.mitpressjournals.org/doi/pdf/10.1162/artl_a_00319)
- [The Surprising Creativity of Digital Evolution](https://direct.mit.edu/artl/article-pdf/26/2/274/1896071/artl_a_00319.pdf)
- [The Surprising Creativity of Digital Evolution - MIT Press Direct](https://direct.mit.edu/artl/article/26/2/274/93255/The-Surprising-Creativity-of-Digital-Evolution-A)
- [Norman H. Packard, and Steen Rasmussen - MIT Press Direct](https://direct.mit.edu/books/book-pdf/2525366/book_9780262291071.pdf)
- [The genotype-phenotype map of an evolving digital organism](https://journals.plos.org/ploscompbiol/article/file?id=10.1371/journal.pcbi.1005414&type=printable)
