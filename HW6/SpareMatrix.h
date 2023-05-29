# include <map>
# include <cstddef>

template<typename T, T defaultValue>
class SpareMatrix {
public:
    using Coordinate = std::pair<int, int>;

    class Row {
    public:
        Row(SpareMatrix* matrix, int x) : matrix_(matrix) { coord_.first = x; }

        Row& operator[](int y) {
            coord_.second = y;
            return *this;
        }

        Row& operator=(T val) {
            matrix_->add(coord_, val);
            return *this;
        }

        operator T() {
            return matrix_->get(coord_);
        }

    private:
        Coordinate coord_;
        SpareMatrix* matrix_;

    };

    size_t size() {
        return values_.size();
    }

    auto begin() const {
        return values_.begin();
    }

    auto end() const {
        return values_.end();
    }

    Row operator[](int ind) {
        Row row(this, ind);
        return row;
    }

    void add(Coordinate xy, T value) {
        if(value != defaultValue) {
            values_[xy] = value;
        } else {
            if(values_.count(xy) != 0) {
                values_.erase(xy);
            }
        }
    }

    T get(Coordinate  xy) {
        if(values_.count(xy) == 0) {
            return defaultValue;
        }

        return values_[xy];
    }

private:
    std::map<Coordinate, T> values_;

};