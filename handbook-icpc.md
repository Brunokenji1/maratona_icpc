# Handbook ICPC: do zero até a Final Brasileira

Material de preparação para a Maratona SBC de Programação (etapa brasileira do ICPC), em C++17. Escrito para um time de três pessoas que está começando em programação competitiva agora, com alvo de classificar da Primeira Fase para a Final Brasileira.

> **Como ler isto.** Este handbook é a espinha dorsal do estudo, não a enciclopédia. Cada tópico tem teoria curta, quando usar, armadilhas, código de referência e um problema para praticar. A profundidade de verdade está nos recursos canônicos listados no fim (CP-Algorithms, CSES, Competitive Programmer's Handbook). Você fica bom resolvendo problema, não lendo. Use isto para saber **o que** estudar, **em que ordem**, e **o que pular**.

---

## 0. A verdade sobre o que a prova cobra

A estrutura no Brasil, em 2026: a Primeira Fase acontece em um único dia (marcada para 29 de agosto de 2026), e os classificados vão para a Final Brasileira (em Uberlândia, 5 a 8 de novembro de 2026). A Final Brasileira é parte da super-regional latino-americana do ICPC. Confirme datas e regras na edição do ano no site oficial (maratona.sbc.org.br), porque isso muda.

O formato: três pessoas, **um computador só**, cinco horas, dez ou mais problemas. O time recebe um caderno de problemas em inglês ou português. Vence quem resolve mais problemas; empate é desempatado pela soma do tempo de cada acerto mais penalidade por tentativas erradas.

Dois números que definem sua estratégia:

1. **O piso para classificar é resolver pelo menos 2 problemas na Primeira Fase.** Abaixo disso o time nem entra na disputa por vaga.
2. Resolver 2 é o mínimo; para classificar de fato (as vagas são limitadas e disputadas), mirar **4 ou mais** coloca um time iniciante em posição competitiva na maioria das sedes. Não tenho o corte exato de vagas por sede (isso varia por ano e por região), então trate "4+" como meta de trabalho, não como garantia.

O que isso significa na prática: **vocês não precisam ser feras em tudo.** Precisam ser sólidos no básico-intermediário e impecáveis em execução. Um time iniciante que resolve com segurança problemas de implementação, busca, grafos básicos e DP simples bate muito time que sabe teoria avançada mas trava no editor sob pressão.

---

## 1. C++ para quem vem de Java ou Python

Você já programa. O que muda aqui é a sintaxe e a obsessão com velocidade. C++ é padrão na maratona porque é rápido (a diferença entre passar e tomar TLE costuma ser o tempo de execução), tem a STL (biblioteca de estruturas prontas e testadas) e é a linguagem de quase todo material competitivo.

### 1.1 O template base

Cole isto no começo de todo problema:

```cpp
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int,int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // seu código aqui

    return 0;
}
```

O que cada parte faz:

`#include <bits/stdc++.h>` importa praticamente toda a STL de uma vez. É uma extensão do compilador g++ (não é C++ padrão), então em código de produção é horrível, mas na maratona é universal porque economiza tempo de digitação. O ambiente da Maratona usa g++, então funciona.

`ios_base::sync_with_stdio(false); cin.tie(nullptr);` é o I/O rápido. Por padrão, `cin` e `cout` são sincronizados com o stdio do C, o que os deixa lentos. Essas duas linhas dão um ganho grande na leitura. Sem isso, problemas com entrada grande dão TLE. Importante: depois disso, **não misture** `cin/cout` com `scanf/printf` no mesmo programa.

`typedef long long ll;` cria um apelido. `long long` é inteiro de 64 bits. Você vai usar muito.

### 1.2 Tipos e overflow: o erro número 1 dos iniciantes

Em C++, os inteiros têm tamanho fixo e **overflow não dá erro**: ele acontece silenciosamente e você perde a questão sem entender por quê.

| Tipo | Tamanho | Vai até aproximadamente |
|---|---|---|
| `int` | 32 bits | 2,1 bilhões (2.147.483.647) |
| `long long` | 64 bits | 9,2 quintilhões (cerca de 9,2 × 10^18) |
| `unsigned long long` | 64 bits | cerca de 1,8 × 10^19 (só não-negativos) |

Regra de sobrevivência: **se o problema envolve multiplicação, soma de muitos valores, ou contagem que pode passar de 2 bilhões, use `long long` por padrão.** Multiplicar dois `int` que cabem em `int` individualmente ainda pode estourar no produto. Exemplo clássico:

```cpp
int a = 100000, b = 100000;
long long errado = a * b;        // estoura: a*b é calculado como int (10^10 não cabe)
long long certo  = (long long)a * b;  // força a conta em 64 bits
```

Outra armadilha: **divisão inteira**. `7 / 2` é `3`, não `3.5`. Se quiser fração, force `double`: `7.0 / 2`.

### 1.3 Containers da STL

A estrutura mais usada na maratona, de longe, é o `vector`. É um array dinâmico, parente do `ArrayList` do Java ou da `list` do Python, mas mais rápido.

```cpp
vector<int> a(n);              // vetor de n inteiros, todos 0
vector<int> b(n, -1);          // n inteiros, todos -1
vector<vector<int>> grid(n, vector<int>(m, 0));  // matriz n x m de zeros

a.push_back(5);                // adiciona no fim
a.pop_back();                  // remove do fim
int x = a.back();              // último elemento
int primeiro = a.front();      // primeiro
a.size();                      // quantos elementos
a.clear();                     // esvazia
sort(all(a));                  // ordena (all = a.begin(), a.end())
```

`pair` guarda dois valores juntos. `tuple` guarda mais de dois.

```cpp
pair<int,int> p = {3, 7};
p.first;   // 3
p.second;  // 7

tuple<int,int,int> t = {1, 2, 3};
get<0>(t);  // 1
```

`string` é a string do C++. Suporta `+` para concatenar, `[]` para acessar caractere, `.size()`, `.substr(pos, len)`.

### 1.4 Containers associativos

`set` guarda elementos únicos e ordenados. Inserção, busca e remoção em O(log n).

```cpp
set<int> s;
s.insert(5);
s.insert(5);          // ignorado, já existe
s.count(5);           // 1 se existe, 0 se não
s.erase(5);
// percorrer em ordem crescente:
for (int x : s) cout << x << '\n';
```

`map` é um dicionário ordenado por chave (parente do `HashMap` do Java, mas ordenado e em O(log n)).

```cpp
map<string,int> contagem;
contagem["abc"]++;          // se não existe, cria com 0 e incrementa
contagem["abc"];            // 1
for (auto [chave, valor] : contagem) { /* ... */ }  // structured binding, C++17
```

`multiset` é como `set` mas aceita repetidos. `unordered_set` e `unordered_map` são as versões com tabela hash: operação média O(1), mas sem ordem e com risco de cair para O(n) em casos adversariais (existem problemas montados para quebrar a hash padrão). Para a maioria dos casos de iniciante, `unordered_map` resolve; se tomar TLE inexplicável com muitos acessos, troque por `map`.

### 1.5 Adaptadores

`stack` (pilha, LIFO), `queue` (fila, FIFO), `deque` (fila de duas pontas), `priority_queue` (heap).

```cpp
stack<int> st; st.push(1); st.top(); st.pop();
queue<int> q;  q.push(1); q.front(); q.pop();

priority_queue<int> maxHeap;   // maior no topo (padrão)
priority_queue<int, vector<int>, greater<>> minHeap;  // menor no topo
```

A `priority_queue` é central no Dijkstra. Por padrão é max-heap; com `greater<>` vira min-heap.

### 1.6 Algoritmos prontos da STL

Não reinvente o que já existe e é rápido:

```cpp
sort(all(a));                          // ordena crescente, O(n log n)
sort(all(a), greater<>());             // decrescente
reverse(all(a));                       // inverte
*min_element(all(a));                  // menor valor
*max_element(all(a));                  // maior valor
accumulate(all(a), 0LL);               // soma (use 0LL para somar em long long!)
__gcd(12, 18);                         // MDC, extensão GCC (retorna 6)
// alternativa padrão C++17 (em <numeric>): std::gcd e std::lcm
unique(all(a));                        // remove duplicatas consecutivas (ordene antes)
next_permutation(all(a));              // próxima permutação em ordem
__builtin_popcount(x);                 // conta bits 1 num int (GCC)
__builtin_popcountll(x);               // versão para long long
```

`lower_bound` e `upper_bound` fazem busca binária em containers **já ordenados** e são fundamentais:

```cpp
// em vetor ordenado a:
auto it = lower_bound(all(a), x);  // primeiro elemento >= x
auto it = upper_bound(all(a), x);  // primeiro elemento > x
int pos = lower_bound(all(a), x) - a.begin();  // índice
```

### 1.7 Comparadores e lambdas

Para ordenar por critério customizado:

```cpp
vector<pair<int,int>> v;
// ordena por segundo elemento, depois por primeiro:
sort(all(v), [](const pair<int,int>& a, const pair<int,int>& b) {
    if (a.second != b.second) return a.second < b.second;
    return a.first < b.first;
});
```

A lambda `[](...){...}` é uma função anônima. O comparador deve devolver `true` quando `a` vem antes de `b`. Cuidado: use `<` para crescente, e nunca use `<=` num comparador (causa comportamento indefinido).

### 1.8 Armadilhas de C++ que custam questões

- **Overflow silencioso.** Já falei, mas é o erro mais comum. Na dúvida, `long long`.
- **Divisão inteira.** `5/2 == 2`. Para fração use `double`.
- **`accumulate` somando em int.** `accumulate(all(a), 0)` soma em `int` e estoura. Use `0LL`.
- **Comparar `double` com `==`.** Por erro de ponto flutuante, compare com tolerância: `abs(x - y) < 1e-9`.
- **Indexação fora do vetor.** C++ não avisa, só corrompe memória ou dá Runtime Error. Cheque limites.
- **Não limpar variáveis globais entre casos de teste.** Em problemas com múltiplos casos, esquecer de resetar um vetor global é bug clássico.

---

## 2. Complexidade: a meta-habilidade mais importante

Antes de codar, você precisa estimar se sua ideia cabe no limite de tempo. Isso separa quem perde uma hora numa solução que ia dar TLE de quem percebe em trinta segundos que precisa de outra abordagem.

A regra de bolso (aproximada, varia com a máquina e o tipo de operação): um computador faz da ordem de **10^8 operações simples por segundo**. Os limites de tempo costumam ser de 1 a 3 segundos. Então, olhando o tamanho da entrada N (que o enunciado sempre informa), você estima a complexidade que cabe:

| N até | Complexidade que costuma caber | Exemplo de técnica |
|---|---|---|
| 10 a 12 | O(n!) | força bruta com permutações |
| 20 a 25 | O(2^n) | subconjuntos, bitmask |
| 100 a 500 | O(n^3) | DP, Floyd-Warshall |
| 1.000 a 5.000 | O(n^2) | DP, pares |
| 10^5 a 10^6 | O(n log n) | ordenação, segment tree, busca binária |
| 10^7 a 10^8 | O(n) | leitura linear, two pointers |

Esses cortes são folclore competitivo, não lei física. Use como primeira estimativa, sempre confirmando com o limite de tempo do problema. A lógica de leitura: **olhe o N no enunciado, descubra a complexidade que cabe, e só então escolha o algoritmo.** Se N é 10^5 e sua ideia é O(n^2) (dez bilhões de operações), nem comece, vai dar TLE.

---

## 3. Técnicas fundamentais

São os padrões de raciocínio que aparecem em quase todo problema fácil. Domine estes antes de qualquer coisa avançada.

### 3.1 Busca completa (brute force)

Quando N é pequeno (veja a tabela acima), testar todas as possibilidades é uma solução legítima e muitas vezes a esperada. Não tenha vergonha de força bruta quando ela cabe. Formas comuns: testar todos os subconjuntos com bitmask (N ≤ 20), testar todas as permutações com `next_permutation` (N ≤ 10), ou laços aninhados (N pequeno).

**Pratique:** CSES "Apple Division" (subconjuntos), CSES "Creating Strings" (permutações).

### 3.2 Busca binária

Procurar um valor em um vetor ordenado em O(log n). Na mão (entenda, mesmo usando `lower_bound` na prática):

```cpp
int lo = 0, hi = n - 1, ans = -1;
while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;   // evita overflow de (lo+hi)
    if (a[mid] <= x) { ans = mid; lo = mid + 1; }
    else hi = mid - 1;
}
```

Armadilhas: o cálculo do `mid` como `(lo+hi)/2` pode estourar se os índices forem grandes (use `lo + (hi-lo)/2`); a condição de parada e o off-by-one são as fontes clássicas de bug. Por isso, na prova, prefira `lower_bound`/`upper_bound` quando der.

### 3.3 Busca binária na resposta

Essa assusta os iniciantes e é poderosíssima. A ideia: às vezes a resposta é um número, e existe uma função `check(x)` que diz "é possível atingir x?". Se `check` é monótona (uma vez verdadeira, continua verdadeira, ou vice-versa), você faz busca binária no **valor da resposta**, não em um vetor.

Padrão "menor x tal que `check(x)` é verdadeiro":

```cpp
ll lo = 1, hi = 1e9;          // intervalo de respostas possíveis
while (lo < hi) {
    ll mid = lo + (hi - lo) / 2;
    if (check(mid)) hi = mid;     // mid serve, tenta menor
    else lo = mid + 1;            // mid não serve, precisa maior
}
// lo é a menor resposta válida
```

Quando usar: enunciados do tipo "qual o menor tempo / a maior capacidade / o menor valor máximo tal que...". O sinal é uma resposta numérica com uma propriedade monótona.

**Pratique:** CSES "Factory Machines", CSES "Array Division".

### 3.4 Two pointers e sliding window

Dois índices que percorrem o vetor de forma coordenada, resolvendo em O(n) o que pareceria O(n^2). Sliding window (janela deslizante) é o caso de "maior/menor subarray contíguo que satisfaz alguma condição": você expande a janela pela direita e encolhe pela esquerda mantendo a condição.

```cpp
// exemplo: maior subarray com soma <= K
int l = 0; ll soma = 0, melhor = 0;
for (int r = 0; r < n; r++) {
    soma += a[r];
    while (soma > K) { soma -= a[l]; l++; }   // encolhe pela esquerda
    melhor = max(melhor, (ll)(r - l + 1));
}
```

**Pratique:** CSES "Subarray Sums II", CSES "Playlist".

### 3.5 Somas de prefixo (prefix sums)

Truque simples e usadíssimo: pré-computar somas acumuladas para responder "soma do intervalo [l, r]" em O(1).

```cpp
vector<ll> pre(n + 1, 0);
for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + a[i];
// soma de a[l..r] (índices 0-based, inclusive) = pre[r + 1] - pre[l]
```

Funciona em 2D também (somas de submatrizes). É a base de muitos problemas de range query. Aprenda cedo, é barato e rende muito.

**Pratique:** CSES "Range Sum Queries I", CSES "Forest Queries" (2D).

### 3.6 Greedy (guloso)

Tomar a melhor decisão local a cada passo, na esperança de que leve ao ótimo global. Funciona em alguns problemas e falha em outros; o difícil é **provar** que o guloso está correto. Exemplos clássicos: agendamento de intervalos (escolher sempre o que termina mais cedo), troco com moedas canônicas.

Aviso de professor: iniciantes adoram greedy porque é fácil de codar, e tomam WA porque o guloso parecia certo mas não era. Se você não consegue argumentar por que o guloso é ótimo, desconfie e considere DP.

**Pratique:** CSES "Tasks and Deadlines", CSES "Movie Festival".

### 3.7 Recursão e backtracking

Backtracking é busca completa com poda: você constrói uma solução incrementalmente e abandona um caminho assim que ele se mostra inviável. Clássico: as N rainhas, gerar combinações, resolver labirintos.

```cpp
void backtrack(int pos, vector<int>& atual) {
    if (pos == n) { /* registra solução */ return; }
    for (int escolha : opcoes(pos)) {
        if (valido(escolha)) {
            atual.push_back(escolha);
            backtrack(pos + 1, atual);
            atual.pop_back();          // desfaz: o "back" do backtracking
        }
    }
}
```

**Pratique:** CSES "Chessboard and Queens", CSES "Grid Paths".

---

## 4. Estruturas de dados

### 4.1 Union-Find (DSU, Disjoint Set Union)

Mantém grupos disjuntos e responde "esses dois elementos estão no mesmo grupo?" e "una estes dois grupos", quase em O(1) amortizado com as duas otimizações (compressão de caminho e união por rank). É a espinha do Kruskal e de qualquer problema de conectividade.

```cpp
struct DSU {
    vector<int> pai, rnk;
    DSU(int n) : pai(n), rnk(n, 0) {
        iota(pai.begin(), pai.end(), 0);   // pai[i] = i
    }
    int find(int x) {
        return pai[x] == x ? x : pai[x] = find(pai[x]);  // compressão de caminho
    }
    bool une(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;          // já estavam juntos
        if (rnk[a] < rnk[b]) swap(a, b);
        pai[b] = a;
        if (rnk[a] == rnk[b]) rnk[a]++;
        return true;
    }
};
```

**Pratique:** CSES "Road Construction".

### 4.2 Fenwick Tree (BIT, árvore indexada binária)

Responde soma de prefixo com atualização de ponto, ambos em O(log n). Mais curta de implementar que a segment tree, resolve o caso comum de "atualize um elemento, pergunte soma de intervalo".

```cpp
struct BIT {
    vector<ll> t;
    int n;
    BIT(int n) : n(n), t(n + 1, 0) {}
    void add(int i, ll v) {            // soma v na posição i (1-based)
        for (; i <= n; i += i & (-i)) t[i] += v;
    }
    ll sum(int i) {                    // soma de [1..i]
        ll s = 0;
        for (; i > 0; i -= i & (-i)) s += t[i];
        return s;
    }
    ll range(int l, int r) { return sum(r) - sum(l - 1); }
};
```

O truque `i & (-i)` isola o bit menos significativo; é o que faz a estrutura andar pela árvore. Não precisa entender a fundo para usar, mas vale ler a explicação no CP-Algorithms.

**Pratique:** CSES "Dynamic Range Sum Queries".

### 4.3 Segment Tree (esticar)

Mais geral que a Fenwick: responde queries de intervalo (soma, mínimo, máximo, etc.) com atualização, em O(log n). É mais código e mais conceito. Para o nível de classificar a Primeira Fase, **deixe para depois de dominar tudo acima.** Muitos problemas de regional não exigem segment tree, e os que exigem geralmente não são os 4 a 6 primeiros que vocês vão querer resolver. Quando chegar a hora, estude no CP-Algorithms e implemente a versão iterativa simples primeiro.

### 4.4 Sparse Table (esticar, opcional)

Responde queries de mínimo/máximo de intervalo em O(1) **sem atualizações**, após pré-processamento O(n log n). Útil e elegante, mas opcional para o alvo inicial.

---

## 5. Grafos

O bloco com mais "ponto fácil" na maratona depois de implementação. Muito problema é um grafo disfarçado: cidades e estradas, estados de um jogo, dependências entre tarefas. Aprender a **enxergar o grafo** no enunciado é metade do trabalho.

### 5.1 Representação

A forma padrão é lista de adjacência:

```cpp
int n, m;                                  // n vértices, m arestas
vector<vector<int>> adj(n);                // grafo não ponderado
for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);                   // remova esta linha se for direcionado
}

// com pesos:
vector<vector<pair<int,int>>> adjP(n);     // {vizinho, peso}
```

Cuidado com a indexação: muitos enunciados numeram vértices de 1 a n. Decida se você trabalha 0-based ou 1-based e seja consistente (dimensione os vetores com `n+1` se for 1-based).

### 5.2 BFS (busca em largura)

Visita o grafo por camadas. Em grafo **não ponderado**, dá o caminho mínimo (menor número de arestas) da origem a todos os vértices.

```cpp
vector<int> dist(n, -1);
queue<int> q;
dist[src] = 0;
q.push(src);
while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
        if (dist[v] == -1) {           // ainda não visitado
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
}
```

Use BFS quando: caminho mínimo com pesos iguais (ou sem peso), distância em labirinto, "nível" de cada nó.

**Pratique:** CSES "Counting Rooms", CSES "Labyrinth".

### 5.3 DFS (busca em profundidade)

Vai fundo num caminho antes de voltar. Base para componentes conexas, detecção de ciclo, ordenação topológica.

```cpp
vector<bool> vis(n, false);
void dfs(int u) {
    vis[u] = true;
    for (int v : adj[u])
        if (!vis[v]) dfs(v);
}
```

Aviso importante: DFS recursiva em grafo muito grande (centenas de milhares de nós em linha) pode estourar a pilha de chamadas (stack overflow, Runtime Error). Se isso acontecer, reescreva a DFS de forma iterativa usando uma `stack` explícita.

**Pratique:** CSES "Building Roads" (conta componentes).

### 5.4 Ordenação topológica

Para grafos direcionados acíclicos (DAG): uma ordem dos vértices tal que toda aresta aponta "para frente". Resolve dependências (compilação, pré-requisitos de tarefas). Versão por BFS (algoritmo de Kahn):

```cpp
vector<int> indeg(n, 0);
for (int u = 0; u < n; u++)
    for (int v : adj[u]) indeg[v]++;

queue<int> q;
for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);

vector<int> ordem;
while (!q.empty()) {
    int u = q.front(); q.pop();
    ordem.push_back(u);
    for (int v : adj[u])
        if (--indeg[v] == 0) q.push(v);
}
// se ordem.size() < n, o grafo tem ciclo
```

**Pratique:** CSES "Course Schedule".

### 5.5 Dijkstra

Caminho mínimo de uma origem a todos os vértices, em grafo com **pesos não negativos**. Com `priority_queue`, roda em O((V + E) log V).

```cpp
vector<ll> dist(n, LLONG_MAX);
priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;  // min-heap
dist[src] = 0;
pq.push({0, src});
while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;             // entrada obsoleta, ignora
    for (auto [v, w] : adjP[u]) {
        if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
    }
}
```

Armadilha crítica: **Dijkstra não funciona com pesos negativos.** Se houver aresta negativa, use Bellman-Ford. A linha `if (d > dist[u]) continue;` é essencial para a performance (descarta entradas velhas da fila).

**Pratique:** CSES "Shortest Routes I".

### 5.6 Bellman-Ford

Caminho mínimo que **aceita pesos negativos** e ainda detecta ciclos negativos. Mais lento: O(V × E). Ideia: relaxar todas as arestas V-1 vezes.

```cpp
vector<ll> dist(n, LLONG_MAX);
dist[src] = 0;
for (int i = 0; i < n - 1; i++)
    for (auto [u, v, w] : arestas)         // arestas como (origem, destino, peso)
        if (dist[u] != LLONG_MAX && dist[u] + w < dist[v])
            dist[v] = dist[u] + w;
// uma V-ésima passada que ainda relaxa indica ciclo negativo
```

Use quando há pesos negativos ou quando o problema pede para detectar ciclo negativo.

### 5.7 Floyd-Warshall

Caminho mínimo entre **todos os pares** de vértices, em O(V^3). Só serve para grafos pequenos (V até algumas centenas, pela tabela de complexidade). Código curtíssimo:

```cpp
// dist[i][j] inicializado com peso da aresta, INF se não há, 0 na diagonal
for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (dist[i][k] < INF && dist[k][j] < INF)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
```

A checagem `< INF` antes de somar evita overflow. Use quando V é pequeno e você precisa de todas as distâncias.

**Pratique:** CSES "Shortest Routes II".

### 5.8 Árvore geradora mínima (MST): Kruskal

Conecta todos os vértices com o menor custo total de arestas. Kruskal: ordene as arestas por peso e vá adicionando a menor que não forme ciclo (usando DSU para detectar ciclo).

```cpp
// arestas: vector de (peso, u, v); DSU definido na seção 4.1
sort(all(arestas));
DSU dsu(n);
ll custo = 0;
for (auto [w, u, v] : arestas)
    if (dsu.une(u, v))        // une devolve false se já conectados
        custo += w;
```

Prim é a alternativa (cresce a árvore a partir de um vértice, parecido com Dijkstra). Para iniciante, Kruskal com DSU é mais direto.

**Pratique:** CSES "Road Reparation".

### 5.9 Avançado (esticar): LCA e componentes fortemente conexas

LCA (ancestral comum mais baixo em árvores) e SCC (componentes fortemente conexas, via Tarjan ou Kosaraju) são tópicos importantes, mas **não prioritários** para classificar a Primeira Fase. Deixe para quando o básico de grafos estiver automático. Quando chegar lá, CP-Algorithms tem ambos.

---

## 6. Programação Dinâmica

Aqui mora a decisão da prova. DP é o tópico que separa o time que resolve 3 problemas do que resolve 5. Também é o que mais assusta. A boa notícia: existe uma receita para pensar em DP, e os problemas de regional costumam ser variações dos clássicos abaixo.

### 6.1 Como pensar em DP

DP serve para problemas onde a resposta se constrói a partir de respostas de subproblemas menores, **e esses subproblemas se repetem**. A receita:

1. **Defina o estado.** O que descreve um subproblema? Geralmente algo como "dp[i] = melhor resposta considerando os primeiros i elementos" ou "dp[i][j] = resposta para o item i com capacidade j".
2. **Escreva a transição.** Como dp[estado] se calcula a partir de estados menores?
3. **Defina o caso base.** O subproblema trivial.
4. **Defina a ordem de cálculo.** De baixo para cima (tabulação) ou recursão com memoização (top-down).

Memoização: você escreve a recursão natural e guarda resultados já calculados num vetor para não recomputar. Tabulação: você preenche a tabela iterativamente, dos casos base para o resultado. As duas são equivalentes; comece com a que for mais intuitiva para você (memoização costuma ser mais fácil de derivar).

### 6.2 Knapsack 0/1 (mochila)

Dados itens com peso e valor, e capacidade W, maximize o valor sem estourar a capacidade. Cada item entra ou não (0/1).

```cpp
vector<int> dp(W + 1, 0);
for (int i = 0; i < n; i++)
    for (int w = W; w >= peso[i]; w--)        // de trás para frente!
        dp[w] = max(dp[w], dp[w - peso[i]] + valor[i]);
// resposta: dp[W]
```

Por que iterar a capacidade **de trás para frente**: para garantir que cada item seja usado no máximo uma vez. Se você iterar para frente, estaria permitindo reusar o mesmo item (que é a variante "unbounded knapsack", onde itens são ilimitados). Esse detalhe de direção é o tipo de coisa que rende WA silencioso.

**Pratique:** CSES "Book Shop".

### 6.3 Coin change (troco)

De quantas formas formar um valor com moedas dadas? Ou: menor número de moedas? Variações de mochila.

```cpp
// menor número de moedas para formar 'alvo':
vector<int> dp(alvo + 1, INF);
dp[0] = 0;
for (int v = 1; v <= alvo; v++)
    for (int moeda : moedas)
        if (v - moeda >= 0 && dp[v - moeda] != INF)
            dp[v] = min(dp[v], dp[v - moeda] + 1);
```

**Pratique:** CSES "Coin Combinations I", CSES "Minimizing Coins".

### 6.4 LIS (maior subsequência crescente)

Maior subsequência (não precisa ser contígua) estritamente crescente. Existe a versão O(n^2) (mais fácil de entender) e a O(n log n) (a que você quer na prova):

```cpp
vector<int> tails;
for (int x : a) {
    auto it = lower_bound(all(tails), x);
    if (it == tails.end()) tails.push_back(x);
    else *it = x;
}
// tamanho da LIS estritamente crescente = tails.size()
// para não-decrescente, troque lower_bound por upper_bound
```

Detalhe: `tails` no fim **não é** a subsequência em si (os valores não são a resposta), mas o **tamanho** está correto. Reconstruir a subsequência exige guardar índices.

**Pratique:** CSES "Increasing Subsequence".

### 6.5 LCS (maior subsequência comum) e distância de edição

LCS: maior subsequência comum a duas strings. Edit distance: menor número de inserções, remoções e substituições para transformar uma string na outra. Ambas são DP 2D clássica. LCS:

```cpp
// dp[i][j] = LCS dos primeiros i de A e j de B
vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
        if (A[i-1] == B[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
        else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
```

**Pratique:** CSES "Edit Distance".

### 6.6 DP em grade

Contar caminhos numa matriz, ou achar o caminho de custo mínimo/máximo, andando só para baixo e para a direita. Estado natural: dp[i][j] = resposta para chegar na célula (i, j).

```cpp
// número de caminhos do canto superior esquerdo ao inferior direito:
vector<vector<ll>> dp(n, vector<ll>(m, 0));
dp[0][0] = (grid[0][0] != bloqueado);
for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
        if (grid[i][j] == bloqueado) { dp[i][j] = 0; continue; }
        if (i > 0) dp[i][j] += dp[i-1][j];
        if (j > 0) dp[i][j] += dp[i][j-1];
        dp[i][j] %= MOD;                  // contagens grandes pedem módulo
    }
```

**Pratique:** CSES "Grid Paths" (o de DP, contagem).

### 6.7 DP em intervalo, em árvore e bitmask (esticar)

- **DP em intervalo:** estado dp[l][r] sobre subsegmentos. Clássico: multiplicação de cadeias de matrizes, problemas de "remover/juntar" extremidades.
- **DP em árvore:** DP onde o estado é um nó e a transição combina os filhos. Resolve muitos problemas de árvore.
- **Bitmask DP:** estado inclui um conjunto representado em bits (N ≤ 20). Clássico: caixeiro viajante com poucas cidades.

São o próximo degrau depois dos clássicos acima. Não pule a base para chegar aqui.

---

## 7. Matemática

A maratona quase sempre tem um ou dois problemas matemáticos. O retorno por hora de estudo aqui é menor que em grafos e DP, mas alguns tópicos são baratos e aparecem muito.

### 7.1 Aritmética modular

Quando contagens ficam enormes, o enunciado pede a resposta "módulo 10^9 + 7" (ou 998244353). Você opera sempre tirando o resto. Propriedades:

```
(a + b) mod m = ((a mod m) + (b mod m)) mod m
(a * b) mod m = ((a mod m) * (b mod m)) mod m
```

Cuidado: subtração pode dar negativo, então some `m` antes do módulo: `((a - b) % m + m) % m`. E multiplicação de dois números próximos de 10^9 estoura `int`; faça em `long long`.

### 7.2 Exponenciação rápida

Calcular base^exp em O(log exp), essencial com módulo:

```cpp
ll power(ll base, ll exp, ll mod) {
    ll res = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}
```

Funciona porque qualquer expoente se decompõe em potências de 2 (os bits do expoente). Atenção ao overflow: como `base < mod`, se `mod` for até cerca de 10^9, o produto `base * base` cabe em `long long`. Para módulos maiores que isso, seria preciso `__int128` ou multiplicação modular cuidadosa.

### 7.3 MDC, MMC e inverso modular

```cpp
ll g = __gcd(a, b);                 // MDC (extensão GCC); padrão: std::gcd
ll mmc = a / __gcd(a, b) * b;       // divida antes de multiplicar (evita overflow)
```

Inverso modular (para "dividir" em aritmética modular) quando o módulo é primo, pelo pequeno teorema de Fermat: o inverso de `a` é `power(a, mod - 2, mod)`. Isso aparece em combinatória modular.

### 7.4 Crivo de Eratóstenes

Marca todos os primos até N em O(N log log N):

```cpp
vector<bool> primo(N + 1, true);
primo[0] = primo[1] = false;
for (int i = 2; (ll)i * i <= N; i++)
    if (primo[i])
        for (int j = i * i; j <= N; j += i)   // começa em i*i, não em 2i
            primo[j] = false;
```

Começar em `i*i` e pular de `i` em `i` é a otimização padrão. Uma variante guarda o menor fator primo de cada número, útil para fatorar rápido depois.

**Pratique:** CSES "Counting Divisors".

### 7.5 Combinatória básica

Contagem com combinações (n escolhe k), arranjos, princípio multiplicativo. Em problemas modulares, pré-compute fatoriais e seus inversos modulares para responder cada combinação em O(1). Aprenda a identificar quando o problema é "quantas formas de..." (combinatória) versus "qual a melhor forma de..." (DP ou greedy).

---

## 8. Strings

Aparece menos que grafos e DP, mas quando aparece e você não sabe a técnica, perde a questão inteira.

### 8.1 Hashing de strings

Transformar uma string num número, para comparar substrings em O(1). A ideia: tratar a string como um número numa base, módulo um primo grande. Comparações de substrings ficam baratas com hashes de prefixo.

Aviso honesto: hashing tem **risco de colisão** (duas strings diferentes com mesmo hash). Em problemas adversariais, hash único pode tomar WA; a defesa é usar **hash duplo** (dois pares base/módulo diferentes). A implementação robusta tem detalhes; estude a versão completa no CP-Algorithms antes de confiar nela na prova. Não vou colar aqui uma versão simplificada que pode te dar falsa segurança.

### 8.2 KMP (Knuth-Morris-Pratt)

Busca de padrão em texto em O(n + m), sem o retrocesso da busca ingênua. O coração é a "função de prefixo" (também chamada de função de falha), que para cada posição diz o tamanho do maior prefixo que também é sufixo:

```cpp
vector<int> prefixo(const string& s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
```

Com a função de prefixo do padrão, você acha todas as ocorrências dele no texto. Para muitos casos de iniciante, hashing resolve os mesmos problemas com código mais simples; aprenda KMP quando precisar da garantia determinística (sem risco de colisão).

### 8.3 Z-function e suffix array (esticar)

Tópicos avançados de strings. Pule para o alvo inicial.

---

## 9. Geometria

Prioridade baixa. Costuma cair pouco, e quando cai é cheia de cuidado com ponto flutuante e casos de borda. Mas o conceito-base, **produto vetorial e orientação**, é simples e às vezes destrava um problema:

```cpp
// sinal do produto vetorial dos vetores OA e OB
// > 0: B está à esquerda de OA (anti-horário); < 0: à direita; = 0: colinear
ll cross(pair<ll,ll> O, pair<ll,ll> A, pair<ll,ll> B) {
    return (A.first - O.first) * (B.second - O.second)
         - (A.second - O.second) * (B.first - O.first);
}
```

Use coordenadas inteiras e `long long` sempre que possível, para evitar erro de ponto flutuante. Só vá além disso (envoltória convexa, interseção de segmentos) se sobrar tempo na preparação.

---

## 10. Estratégia de prova e dinâmica de time

Aqui está o ganho mais subestimado. Dois times com o mesmo conhecimento técnico têm resultados muito diferentes dependendo da estratégia. Como vocês são três com **um computador só**, isso é decisivo.

### 10.1 Divisão de papéis

Um digita, os outros dois leem e pensam. O tempo de teclado é o recurso mais escasso. Com a especialização que vai surgir nos treinos (um mais forte em grafos, outro em DP, outro em implementação e matemática), o dono do tema senta para codar quando aparece um problema da área dele.

### 10.2 Os primeiros 15 minutos

No começo da prova, **dividam o caderno e leiam todos os problemas.** Cada um lê um terço e classifica: fácil, médio, difícil, sei resolver, não sei. Isso evita o erro fatal de empacar no problema A enquanto o problema H era trivial e ninguém leu. Ataquem os fáceis primeiro, pela ordem de confiança, não pela ordem das letras.

### 10.3 Penalidade e tempo

O placar penaliza tempo: cada acerto soma o minuto em que foi feito, e cada submissão errada antes do acerto adiciona uma penalidade (geralmente 20 minutos). Implicações práticas: resolva os fáceis cedo (vale menos tempo acumulado), e **não submeta no chute** (cada erro custa penalidade). Teste localmente antes de submeter.

### 10.4 Stress testing: a técnica que salva a prova

Quando você toma WA e não acha o bug, stress testing acha em minutos. Você escreve uma solução "burra" (força bruta, obviamente correta, mesmo que lenta) e um gerador de casos aleatórios pequenos, e um script roda as duas em loop comparando a saída. No primeiro caso em que divergirem, você tem um contra-exemplo mínimo que expõe o bug.

Montem isso juntos no repositório do time antes da prova. É uma das melhores ferramentas que um time iniciante pode ter, e quase ninguém usa.

### 10.5 O team notebook

Vocês podem levar um caderno impresso com códigos de referência (confira o limite de páginas e as regras da edição). Esse caderno deve ter as implementações que vocês testaram e entendem: template, DSU, Dijkstra, BFS/DFS, knapsack, crivo, KMP, e por aí vai. O site que vocês construíram (módulo Team Notebook) exporta exatamente isso em PDF. Regra de ouro: **só vá para o caderno código que vocês já usaram para resolver um problema real.** Código copiado que ninguém testou é fonte de WA.

### 10.6 O que cada veredito significa

- **AC (Accepted):** passou. Comemore baixinho e vá para o próximo.
- **WA (Wrong Answer):** saída errada em algum caso. Reveja a lógica, casos de borda, overflow. Stress test.
- **TLE (Time Limit Exceeded):** lento demais. Sua complexidade não cabe; reveja a tabela da seção 2.
- **RE (Runtime Error):** crash. Acesso fora do vetor, divisão por zero, stack overflow (DFS profunda), recursão infinita.
- **MLE (Memory Limit Exceeded):** memória demais. Estruturas grandes demais ou vazamento.
- **CE (Compilation Error):** nem compilou. Erro de sintaxe; leia a mensagem do compilador.

---

## 11. Plano de 20 semanas

Recapitulando o cronograma, agora amarrado ao conteúdo acima. Treino de time (um contest virtual de 2 a 5 horas) **toda semana**, sem exceção, a partir da semana 3.

**Fase 1, semanas 1 a 3, fluência em C++ e implementação.** Seções 1 e 2 deste handbook. Resolver 40 a 60 problemas rating 800 a 1000 no Codeforces. Objetivo: parar de pensar em sintaxe.

**Fase 2, semanas 4 a 7, fundação algorítmica.** Seção 3 inteira (busca binária, two pointers, prefix sums, greedy, backtracking). Problemas rating 1000 a 1300. Começam os treinos de time semanais.

**Fase 3, semanas 8 a 12, estruturas e grafos.** Seções 4.1, 4.2 e 5 inteira. DSU, BFS, DFS, Dijkstra, topológica, MST. Problemas rating 1200 a 1500. É onde a maioria desiste; não desistam.

**Fase 4, semanas 13 a 17, DP e matemática.** Seções 6 e 7. Os clássicos de DP e a matemática barata. Problemas rating 1300 a 1600. **Esta fase decide a classificação.**

**Fase 5, semanas 18 a 20, strings e polimento.** Seção 8 (hashing, KMP), montagem do team notebook impresso, e simulados completos de 5 horas com provas de edições antigas da Primeira Fase e da Final Brasileira.

---

## 12. Recursos canônicos

Estes são os materiais de referência reais do mundo competitivo. Confira os links, porque endereços mudam.

**Para aprender (gratuitos):**
- *Competitive Programmer's Handbook*, de Antti Laaksonen. PDF gratuito, é o material padrão de entrada. Disponível em cses.fi/book.
- *CP-Algorithms* (cp-algorithms.com): enciclopédia de algoritmos competitivos com implementações. A referência que vocês vão abrir mais.
- *USACO Guide* (usaco.guide): trilha estruturada por nível, excelente para iniciantes, com problemas selecionados.

**Para praticar:**
- *Codeforces* (codeforces.com): a plataforma principal. Contests semanais, sistema de rating que diz onde vocês estão, editoriais. Comecem nas divisões 3 e 4.
- *AtCoder* (atcoder.jp): problemas de qualidade educacional altíssima. Os "Beginner Contests" (ABC) são ótimos.
- *CSES Problem Set* (cses.fi/problemset): coleção curada por tópico, do mesmo autor do handbook. Praticamente todos os problemas que citei aqui estão lá, organizados exatamente pelos temas deste documento. **É o melhor lugar para vocês praticarem de forma organizada.**

**Plataformas brasileiras:** existem juízes e plataformas com foco no Brasil e na Maratona (por exemplo, juízes online brasileiros e plataformas de treino nacionais). Confirmem quais estão ativas e quais a Fatec ou o treinador de vocês recomenda, porque esse cenário muda.

**Inspiração para o team notebook (avançado):** o KACTL, caderno de competição da KTH, é referência mundial de notebook (github.com/kth-competitive-programming/kactl). É nível avançado; usem como inspiração de organização, não como ponto de partida.

---

## 13. O que pular (para não perder tempo)

Tão importante quanto o que estudar. Para o alvo de classificar a Primeira Fase, **adiem** ou ignorem por enquanto: segment tree com lazy propagation, fluxo máximo, matching, FFT/NTT, suffix automaton, geometria avançada (envoltória convexa, varredura), e a maior parte da matemática pesada (teoria dos números avançada). Esses tópicos rendem em níveis mais altos (Final Brasileira de elite, Latino-americana, Mundial), mas para um time iniciante eles roubam tempo que renderia muito mais em DP e grafos básicos.

A armadilha clássica do iniciante ambicioso é estudar o tópico difícil e impressionante em vez de ficar impecável no básico que cai mais. Resista. Vinte algoritmos que vocês dominam e implementam de olhos fechados valem mais que oitenta que vocês meio que conhecem.

---

## Resumo de uma frase

Fiquem sólidos em implementação, busca, grafos básicos e DP simples; treinem em time toda semana; usem stress testing; e resolvam centenas de problemas no CSES e no Codeforces. O resto é detalhe.
