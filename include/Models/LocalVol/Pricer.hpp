// SPDX-License-Identifier: Apache-2.0
/*
 * File:        Pricer.hpp
 * Author:      Alvaro Sanchez de Carlos
 * Created:     2025-12-08
 *
 * Description:
 *   [Brief description of what this file declares or implements.]
 *
 * Copyright (c) 2025 Alvaro Sanchez de Carlos
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under this License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the LICENSE for the specific language governing permissions and
 * limitations under this License.
 */

#pragma once

#include "Core/Types.hpp"
#include "Models/LocalVol/AHCache.hpp"

#include <concepts>
#include <cstddef>
#include <span>
#include <array>

namespace uv::models::localvol
{
	template
		<
		std::floating_point T,
		std::size_t NT,
		std::size_t NX
		>
		class Pricer
	{
	private:

		// Market data
		T r_;
		T q_;

		// Grids
		std::array<T, NX> xGrid_;
		std::array<T, NX> c_;
		std::array<T, NX> cInit_;


		// Cached variables and buffers
		AHCache<T, NX> ahCache_{};

	public:

		Pricer() = delete;

		template <typename F>
		Pricer(F&& payoff,
			Vector<T> r,
			Vector<T> q,
			T xBound
		);

		Vector<T> price(T maturity,
			std::span<const T> logKF,
			std::span<const T> localVar
		);

	};

} // namespace uv::models::localvol

#include "Pricer.inl"