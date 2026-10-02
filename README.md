# 📚 Sistema de Gestão de Acervo - Livraria & Papelaria

**Descrição:**  
Este projeto prático consiste em um sistema desenvolvido em linguagem C para a gestão e controle de estoque do acervo de uma livraria (incluindo livros de diversos gêneros, artigos de papelaria e produtos culturais). 

O programa utiliza conceitos de estruturas de dados (`struct`), manipulação de arquivos CSV (`.csv`), modularização através de funções e tratamento robusto de validações de entrada para evitar falhas de execução. O sistema garante a persistência dos dados no arquivo `acervo_livraria.csv`, mantendo o histórico de produtos mesmo após o encerramento da execução[cite: 18].

**Turma:** Ads / Ciência da Computação - Grupo 11[cite: 18]

**Integrantes do Grupo:**[cite: 18] 
1. Higor Aparecido da Silva Santos[cite: 18] 
2. Isabella de Almeida Santos[cite: 18] 
3. Edgard Aparecido[cite: 18] 
4. Lucas Rodrigues[cite: 18] 
5. José Bettuz[cite: 18] 

---

## 🛠️ Funcionalidades do Sistema

O sistema conta com um menu interativo e oferece as seguintes operações:

1. **Cadastrar Produto/Item:** Permite registrar um novo item no acervo (Nome, Categoria/Gênero, Preço, Quantidade em Estoque e Código/ISBN) com validações contra valores negativos.
2. **Listar Acervo Completo:** Exibe todos os itens salvos no arquivo CSV de forma organizada.
3. **Buscar por Nome:** Localiza e exibe os detalhes de um produto específico através da comparação de nomes.
4. **Buscar por Categoria/Gênero:** Filtra e lista todos os produtos pertencentes a uma determinada categoria (ex: Ficção, Papelaria, Técnico).
5. **Buscar por Faixa de Preço:** Filtra produtos dentro de um intervalo de preço configurável (com validação para garantir que o preço mínimo não supere o máximo).
6. **Remover Produto:** Exclui um item do acervo reescrevendo o arquivo com o auxílio de um arquivo temporário (`temp.csv`).
7. **Atualizar Dados:** Permite alterar as informações de um produto já cadastrado.

---

## 📁 Estrutura dos Arquivos Persistidos

Os dados são armazenados no formato CSV separado por ponto e vírgula (`;`), com a seguinte estrutura:
`Nome;Categoria;Preco;Quantidade;Codigo`

* **`acervo_livraria.csv`**: Arquivo principal de armazenamento dos dados do acervo.
* **`temp.csv`**: Arquivo auxiliar utilizado temporariamente durante as operações de remoção e atualização.

---

🎥 **[Link da Apresentação no YouTube](COLE_O_LINK_AQUI)**
