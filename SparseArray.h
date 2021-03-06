#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

namespace spandex
{
	template<class T>
	class SparseArray
	{
	public:
		int size;
		int nnz;

	private:
		typedef typename std::vector<std::pair<int, T>>::iterator Iterator;
		typedef typename std::vector<std::pair<int, T>>::const_iterator ConstIterator;

		struct CompareFunc
		{
			CompareFunc() = default;
			bool operator()(const std::pair<int, T>& a, int b) const
			{
				return a.first < b;
			}

			bool operator()(int a, const std::pair<int, T>& b) const
			{
				return a < b.first;
			}
		};

		std::vector<std::pair<int, T>> items;
		CompareFunc compareFunc;

	public:
		SparseArray(int size) : size(size), nnz(0)
		{
		}

		SparseArray(const std::vector<T>& init) : SparseArray((int)init.size())
		{
			int size = (int)init.size();
			for (int i = 0; i < size; i++)
			{
				Insert(i, init[i]);
			}
		}

		SparseArray(int size, std::initializer_list<std::pair<int, T>> init) : SparseArray(size)
		{
			for (auto& item : init)
			{
				Insert(item.first, item.second);
			}
		}

		bool Equals(const SparseArray& that) const
		{
			if (size != that.size)
			{
				return false;
			}
			return items == that.items;
		}

		Iterator begin()
		{
			return items.begin();
		}

		Iterator end()
		{
			return items.end();
		}

		ConstIterator begin() const
		{
			return items.begin();
		}

		ConstIterator end() const
		{
			return items.end();
		}

		void Insert(int index, const T& value)
		{
			assert(index < size);

			auto it = LowerBound(index);
			if (it != end() && !compareFunc(index, *it))
			{
				it->second = value;
			}
			else
			{
				items.emplace(it, index, value);
				nnz += 1;
			}
		}

		bool Contains(int index)
		{
			assert(index < size);

			return end() != Find(index);
		}

		void Clear() noexcept
		{
			nnz = 0;
			items.clear();
		}

		T At(int index)
		{
			assert(index < size);

			auto it = Find(index);

			if (end() == it)
			{
				return T();
			}
			else
			{
				return it->second;
			}
		}

	private:

		Iterator LowerBound(int index)
		{
			return std::lower_bound(items.begin(), end(), index, compareFunc);
		}

		Iterator Find(int index)
		{
			auto it = LowerBound(index);
			if (it != end() && !compareFunc(index, *it))
			{
				return it;
			}

			return end();
		}
	};
}