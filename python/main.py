import numpy as np

def entropy(X):
    probs = [np.mean(X == c) for c in set(X)]
    return sum(-p * np.log2(p) for p in probs)

a = np.array(['a', 'b', 'c', 'd'])
print(entropy(a))


# def entropy(X, Y):
#     probs = []
#     for c1 in set(X):
#         for c2 in set(Y):
#             probs.append(np.mean(np.logical_and(X == c1, Y == c2)))
#             print(c1, c2)

#     print(probs)
#     # return sum(-p * np.log2(p) for p in probs)

# a = np.array(['a', 'b', 'c', 'd'])
# b = np.array(['e', 'f', 'g', 'h'])
# print(entropy(a, a))