# spandex
Fast and simple sparse matrix library

```c++
rope::CommonGraph<double> g(3);
g.Insert(0, 1, 1);
g.Insert(0, 2, 1);
g.Insert(1, 0, 2);
g.Insert(1, 1, 4);
g.Insert(1, 2, -2);
g.Insert(2, 1, 3);
g.Insert(2, 2, 15);
auto a = spandex::SparseMatrix<double>::FromGraph(3, 3, g);

spandex::CholeskySolver<double> solver(3, 3);
solver.permutation = spandex::Permutation::Type::AMD;

solver.SolveSym(a);

std::vector<double> b{ 17, 2.89, -3.3 };

auto x = solver.Solve(a, b);

auto u = solver.Update(spandex::SparseArray<double>(3, { {0, 7.0}, {1, -5.0}, {2, 1.0} }), 9);
```
