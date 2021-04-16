# Nand2Tetris
## by Hebrew University of Jerusalem
Build a modern computer from Nand to Tetris (Project-Centered Course), with the
professors Noam Nisan and Shimon Shocken

# Week 01: Boolean Functions and Gate Logic

## Lecture 01: Boolean Logic

### Truth Tables
#### AND
| x     |  y     | result |
| :------------- | :------------- | :------- |
| 0       | 0       | 0|
| 1 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 1 | 1 |

#### OR
| x     |  y     | result |
| :------------- | :------------- | :------- |
| 0       | 0       | 0|
| 1 | 0 | 1 |
| 0 | 1 | 1 |
| 1 | 1 | 1 |

#### NOT
| x     |  not x     |
| :------------- | :------------- |
| 0       | 1       |
| 1 | 0 |

###  Boolean Identities
#### Commutative Laws
- (x AND y) = (y AND x)
- (x OR y) = (y OR x)

#### Associative Laws
- (x AND (y AND z)) = ((x AND y) AND z)
- (x OR (y OR z)) = ((x OR y) OR z)

#### Distributive Laws
- (x AND (y OR z)) = ((x AND y) OR (x AND z))
- (x OR (y AND z)) = ((x OR y) AND (x OR z))


#### De Morgan Laws
- NOT(x AND y) = NOT(x) OR NOT(y)
- NOT(x OR y) = NOT(x) AND NOT(y)


### Boolean functions from
```
And16.hdl And.hdl DMux4Way.hdl DMux8Way.hdl DMux.hdl Mux16.hdl Mux4Way16.hdl Mux8Way16.hdl Mux.hdl Not16.hdl Not.hdl Or16.hdl Or8Way.hdl Or.hdl Xor.hdl

```
