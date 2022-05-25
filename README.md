# graph-coloring

## MILP Model formulation

### Base Model
$$
\begin{align*}
    \min& \sum_{c \in C} y_c\\
    \text{subject to}&\\
    &\sum_{c \in C} x_{ic} = 1\ \ \ \ \forall i \in V\\
    &x_{ic} + x_{jc} \le 1\ \ \ \ \forall(i, j) \in E, \forall c \in C\\
    &x_{ic} \le y_{ic} \ \ \ \ \forall i \in V, \forall c \in C\\
    &x_{ic} \in \lbrace0, 1\rbrace \ \ \ \ \forall i \in V, \forall c \in C\\
    &y_{c} \in \lbrace0, 1\rbrace\ \ \ \ \forall c \in C\\
\end{align*}
$$


### Branch and Price Model

#### Master Problem
$$
\begin{align*}
    \min& \sum_{p \in P} \lambda_p\\
    \text{subject to}&\\
    &\sum_{p \in P} a_{ip}\lambda_p = 1\ \ \ \ \forall i \in V\\
    &\lambda_p \in \lbrace0, 1\rbrace\ \ \ \ \forall p \in P\\
\end{align*}
$$

#### Pricing Problem
$$
\begin{align*}
    \min&\ \ 1 - \sum_{i \in V} \pi_i x_i\\
    \text{subject to}&\\
    &x_{i} + x_{j} \le 1\ \ \ \ \forall(i, j) \in E, \forall c \in C\\
    &x_{i} \in \lbrace0, 1\rbrace \ \ \ \ \forall i \in V
\end{align*}
$$

