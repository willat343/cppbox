#include "cppbox/classifiers.hpp"

#include <gtest/gtest.h>

#include <limits>
#include <memory>
#include <stdexcept>
#include <vector>

TEST(classifier_base, classify) {
    std::vector<std::unique_ptr<cppbox::ClassifierBase<double>>> classifiers;
    classifiers.push_back(std::make_unique<cppbox::ThresholdClassifier<double>>(2.0));
    classifiers.push_back(std::make_unique<cppbox::SchmittTrigger<double>>(1.0, 3.0));
    // Between the Schmitt trigger thresholds when rising, only the threshold classifier switches to true
    EXPECT_TRUE(classifiers[0]->classify(2.5));
    EXPECT_FALSE(classifiers[1]->classify(2.5));
    // Above all thresholds
    EXPECT_TRUE(classifiers[0]->classify(3.5));
    EXPECT_TRUE(classifiers[1]->classify(3.5));
    // Between the Schmitt trigger thresholds when falling, only the threshold classifier switches to false
    EXPECT_FALSE(classifiers[0]->classify(1.5));
    EXPECT_TRUE(classifiers[1]->classify(1.5));
}

TEST(threshold_classifier, classify) {
    cppbox::ThresholdClassifier<double> classifier(2.0);
    EXPECT_EQ(classifier.threshold(), 2.0);
    EXPECT_FALSE(classifier.classify(-1.0));
    EXPECT_FALSE(classifier.classify(2.0));
    EXPECT_TRUE(classifier.classify(2.5));
    EXPECT_FALSE(classifier.classify(1.5));
}

TEST(threshold_classifier, classify_nan) {
    cppbox::ThresholdClassifier<double> classifier(2.0);
    EXPECT_FALSE(classifier.classify(std::numeric_limits<double>::quiet_NaN()));
}

TEST(schmitt_trigger, construct) {
    const cppbox::SchmittTrigger<double> trigger(1.0, 3.0);
    EXPECT_EQ(trigger.falling_threshold(), 1.0);
    EXPECT_EQ(trigger.rising_threshold(), 3.0);
    EXPECT_FALSE(trigger.state());
    EXPECT_TRUE(cppbox::SchmittTrigger<double>(1.0, 3.0, true).state());
    EXPECT_NO_THROW(cppbox::SchmittTrigger<double>(2.0, 2.0));
    EXPECT_THROW(cppbox::SchmittTrigger<double>(3.0, 1.0), std::invalid_argument);
}

TEST(schmitt_trigger, classify) {
    cppbox::SchmittTrigger<double> trigger(1.0, 3.0);
    // Rising through the band holds false until above the rising threshold
    EXPECT_FALSE(trigger.classify(0.0));
    EXPECT_FALSE(trigger.classify(2.0));
    EXPECT_FALSE(trigger.classify(3.0));
    EXPECT_TRUE(trigger.classify(3.5));
    EXPECT_TRUE(trigger.state());
    // Falling through the band holds true until below the falling threshold
    EXPECT_TRUE(trigger.classify(2.0));
    EXPECT_TRUE(trigger.classify(1.0));
    EXPECT_FALSE(trigger.classify(0.5));
    EXPECT_FALSE(trigger.state());
    // Values within the band hold the state
    EXPECT_FALSE(trigger.classify(2.0));
}

TEST(schmitt_trigger, classify_equal_thresholds) {
    cppbox::SchmittTrigger<double> trigger(2.0, 2.0);
    EXPECT_FALSE(trigger.classify(2.0));
    EXPECT_TRUE(trigger.classify(2.5));
    EXPECT_TRUE(trigger.classify(2.0));
    EXPECT_FALSE(trigger.classify(1.5));
}

TEST(schmitt_trigger, classify_nan) {
    cppbox::SchmittTrigger<double> trigger(1.0, 3.0, true);
    EXPECT_TRUE(trigger.classify(std::numeric_limits<double>::quiet_NaN()));
    trigger.set_state(false);
    EXPECT_FALSE(trigger.classify(std::numeric_limits<double>::quiet_NaN()));
}

TEST(schmitt_trigger, set_state) {
    cppbox::SchmittTrigger<int> trigger(1, 3);
    trigger.set_state(true);
    EXPECT_TRUE(trigger.state());
    EXPECT_TRUE(trigger.classify(2));
    trigger.set_state(false);
    EXPECT_FALSE(trigger.classify(2));
}
