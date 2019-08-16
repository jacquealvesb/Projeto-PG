# Projeto de Processamento Gráfico - Ray Tracing

Projeto da disciplina *IF680 - Processamento Gráfico* do curso de Ciência da Computação no Centro de Informática da Universidade Federal de Pernambuco - UFPE

## Pré-requisitos

Além do **Python 2**, é necessário ter instalado na máquina o Pillow. Para instalar, inserir o comando a seguir no terminal:

```
pip install Pillow==2.2.2
```

## Descrição do projeto

É lido um arquivo de descrição de cena contendo informações da câmera e das superfícies (geometria e materiais) e a cena é criada com tais configurações usando o algoritmo de Ray Tracing. O modelo de iluminação utilizado é o de Phong.

### Parâmetros da câmera

* Tamanho (w h)
* Field of View (fov)
* Posição (pos - px py pz)
* Ponto de Mira (target - tx ty tz)
* Vetor que aponta a orientação (up - ux uy uz)
* Distância para o plano de imagem (f)

### Parâmetros dos materiais

* Fator Emissivo (Ke)
* Fator Difuso (Kd)
* Fator Especular (Ks)
* Coeficiente de Rugosidade (alpha) 
* Cor (c)

### Parâmetros das superfícies (neste caso, esferas)

* Centro (c)
* Raio (r)

### Formato do arquivo de descrição

```
w h
px py pz tx ty tz ux uy uz fov f
nomeMaterial1 r g b kd ks ke alpha
nomeMaterial2 r g b kd ks ke alpha
...
nomeMaterialN r g b kd ks ke alpha

esfera cx cy cz r nomeMaterial1
esfera cx cy cz r nomeMaterial2
...
esfera cx cy cz r nomeMaterialN
```

## Rodando o código

Para rodar o código, inserir o comando a seguir no terminal na pasta do projeto:

```
python main.py
```
