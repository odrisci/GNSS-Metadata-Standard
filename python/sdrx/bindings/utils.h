template <typename Sequence>
inline py::array_t< typename Sequence::value_type> as_pyarray(Sequence&& seq)
{
    Sequence *seq_ptr = new Sequence(std::move(seq));
    auto capsule = py::capsule(seq_ptr, [](void *p){
            delete reinterpret_cast<Sequence*>(p);
            });

    return py_array(seq_ptr->size(), seq_ptr->data
}
