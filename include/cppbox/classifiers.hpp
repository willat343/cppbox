#ifndef CPPBOX_CLASSIFIERS_HPP
#define CPPBOX_CLASSIFIERS_HPP

#include <concepts>

namespace cppbox {

/**
 * @brief Base class of binary classifiers of a value (e.g. as in contact or not), so that the classifier can be chosen
 * at runtime.
 *
 * @tparam T_ value type, totally ordered
 */
template<std::totally_ordered T_>
class ClassifierBase {
public:
    using T = T_;

    /**
     * @brief Destroy the classifier.
     *
     */
    virtual ~ClassifierBase() = default;

    /**
     * @brief Classify a value, updating the state of the classifier if it has one.
     *
     * @param value
     * @return bool classification
     */
    virtual bool classify(const T& value) = 0;
};

/**
 * @brief Binary classifier of a value against a single threshold, classifying it as true (e.g. in contact) if and only
 * if it is greater than the threshold. The classifier is stateless.
 *
 * @tparam T_ value type, totally ordered (for floating point, a NaN value is classified as false)
 */
template<std::totally_ordered T_>
class ThresholdClassifier : public ClassifierBase<T_> {
public:
    using Base = ClassifierBase<T_>;
    using typename Base::T;

    /**
     * @brief Construct a threshold classifier.
     *
     * @param threshold_ threshold above which a value is classified as true
     */
    explicit ThresholdClassifier(const T& threshold_);

    /**
     * @brief Classify a value, \f$ c = v > \theta \f$.
     *
     * @param value
     * @return true if the value is greater than the threshold
     * @return false otherwise
     */
    bool classify(const T& value) override;

    /**
     * @brief Get the threshold \f$ \theta \f$.
     *
     * @return const T&
     */
    const T& threshold() const;

private:
    // Threshold above which a value is classified as true
    T threshold_;
};

/**
 * @brief Binary classifier with hysteresis (a Schmitt trigger), which switches to true when a value rises above the
 * rising threshold, switches to false when a value falls below the falling threshold, and otherwise holds its state.
 * With equal thresholds, it classifies as a `ThresholdClassifier`, except that it holds its state for a value equal to
 * the thresholds.
 *
 * @tparam T_ value type, totally ordered (for floating point, a NaN value holds the state)
 */
template<std::totally_ordered T_>
class SchmittTrigger : public ClassifierBase<T_> {
public:
    using Base = ClassifierBase<T_>;
    using typename Base::T;

    /**
     * @brief Construct a Schmitt trigger.
     *
     * @param falling_threshold_ threshold below which a value switches the state to false
     * @param rising_threshold_ threshold above which a value switches the state to true, which must be greater than
     * or equal to the falling threshold
     * @param state_ initial state
     */
    explicit SchmittTrigger(const T& falling_threshold_, const T& rising_threshold_, const bool state_ = false);

    /**
     * @brief Classify a value, updating and returning the state \f$ c \f$:
     * \f[
     *      c \leftarrow \begin{cases} \text{true} & v > \theta_r \\ \text{false} & v < \theta_f \\ c & \text{otherwise}
     *      \end{cases}
     * \f]
     *
     * @param value
     * @return bool updated state
     */
    bool classify(const T& value) override;

    /**
     * @brief Get the falling threshold \f$ \theta_f \f$.
     *
     * @return const T&
     */
    const T& falling_threshold() const;

    /**
     * @brief Get the rising threshold \f$ \theta_r \f$.
     *
     * @return const T&
     */
    const T& rising_threshold() const;

    /**
     * @brief Set the state, e.g. to reset the classifier.
     *
     * @param state_
     */
    void set_state(const bool state_);

    /**
     * @brief Get the state, i.e. the last classification or the initial state if no value has been classified.
     *
     * @return bool
     */
    bool state() const;

private:
    // Threshold below which a value switches the state to false
    T falling_threshold_;
    // Threshold above which a value switches the state to true
    T rising_threshold_;
    // Current classification
    bool state_;
};

}

#include "cppbox/impl/classifiers.hpp"

#endif
