# Copyright 2013 Joshua Beitler

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

# http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# clean object files, etc.
desc "Clean up all the extra crap"
task :clean do
    sh "rm -f #{$object_files} >/dev/null 2>&1"
    sh "rm -f #{$dep_files} >/dev/null 2>&1"
    sh "rm -f #{$target} >/dev/null 2>&1"
    sh "rm -f #{$target_bin} >/dev/null 2>&1"
    sh "rm -f #{$target_iso} >/dev/null 2>&1"
    sh "rm -f build/*.bin >/dev/null 2>&1"
    sh "rm -f build/*.iso >/dev/null 2>&1"
    sh "rm -f build/*.log >/dev/null 2>&1"
    sh "rm -f iso/boot/kernel.bin >/dev/null 2>&1"
end