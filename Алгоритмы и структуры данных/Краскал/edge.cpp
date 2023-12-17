struct edge {
public:
    int from, to, weight;

    edge() {

    };

    edge(int from, int to, int weight) {
        this->from = from;
        this->to = to;
        this->weight = weight;
    }
};
