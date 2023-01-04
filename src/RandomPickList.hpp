#include <map>
#include <memory>
#include <random>
#include <vector>

template <typename T, typename RNG = std::mt19937> class RandomPickList {
public:
  struct Element {
    T value;
    size_t weight{1};
  };

  explicit RandomPickList(const std::vector<Element>& elements)
      : elements_(elements), generator_(std::make_unique<RNG>())
  {
    // Create a vector of weights
    for (const auto& e : elements_) { weights_.push_back(e.weight); }

    // Seed the generator with a randomly-generated seed value
    std::random_device rd;
    generator_->seed(rd());
  }

  auto PickRandom() -> T
  {
    // Generate a random number using a discrete distribution
    std::discrete_distribution<size_t> distribution(weights_.begin(), weights_.end());
    auto random_number = distribution(*generator_);

    return elements_[random_number].value;
  }

  auto PickRandomEqualWeight() -> T
  {
    // Generate a random number in the range [0, elements_.size())
    std::uniform_int_distribution<size_t> distribution(0, elements_.size() - 1);
    auto random_number = distribution(*generator_);

    return elements_[random_number].value;
  }

  void AddElement(const Element& element)
  {
    elements_.push_back(element);
    weights_.push_back(element.weight);
  }

private:
  std::vector<Element> elements_;
  std::vector<size_t> weights_;
  std::unique_ptr<RNG> generator_;
};