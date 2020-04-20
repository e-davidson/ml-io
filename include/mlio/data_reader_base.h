/*
 * Copyright 2019-2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not use this file except in compliance with the License. A copy of
 * the License is located at
 *
 *      http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF
 * ANY KIND, either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 */

#pragma once

#include "mlio/config.h"
#include "mlio/data_reader.h"
#include "mlio/example.h"
#include "mlio/intrusive_ptr.h"

namespace mlio {
inline namespace v1 {

/// @addtogroup data_readers Data Readers
/// @{

/// Represents an abstract base class for data readers.
class MLIO_API data_reader_base : public data_reader {
protected:
    explicit data_reader_base(data_reader_params &&prm) noexcept;

public:
    intrusive_ptr<example> read_example() final;

    intrusive_ptr<example> peek_example() final;

private:
    /// When implemented in a derived class, returns the next @ref
    /// example read from the dataset.
    virtual intrusive_ptr<example> read_example_core() = 0;

public:
    void reset() noexcept override;

public:
    data_reader_params const &params() const noexcept
    {
        return params_;
    }

protected:
    /// Gets the effective boolean value indicating whether a warning
    /// will be output for each bad instance.
    bool warn_bad_instances() const noexcept
    {
        return warn_bad_instances_;
    }

private:
    data_reader_params params_;
    bool warn_bad_instances_{};
    intrusive_ptr<example> peeked_example_{};
};

/// @}

}  // namespace v1
}  // namespace mlio
