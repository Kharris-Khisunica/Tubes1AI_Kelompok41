import subprocess
import os

base_path = os.path.abspath(os.path.dirname(__file__))
executable_path = os.path.join(base_path, "src", "class", "main")
list_size = "10"

result = subprocess.run([executable_path, list_size], capture_output=True, text=True, check=True)
print(result.stdout)
