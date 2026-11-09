# Development tools

This directory is reserved for small, auditable tools that improve reproducibility.

Before adding a tool:
- document its purpose and dependencies;
- make read-only behavior the default;
- avoid partition writes, firmware flashing, security bypasses, or credential handling;
- provide tests and usage examples;
- never bundle proprietary firmware or signing material.
