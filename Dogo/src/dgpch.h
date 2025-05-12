#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <array>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <utility>
#include <iostream>  
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <filesystem>
#include <codecvt>
#include <locale>
#include <deque>

#ifdef DG_PLATFORM_WINDOWS
	#include "Windows.h"
	#include "windowsx.h"
	#include <wrl/client.h>
	#include <winsdkver.h>
	#include <sdkddkver.h>
	#include <glad/glad.h>
#endif
#ifdef DG_PLATFORM_LINUX
	#include <X11/keysym.h>
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <sys/time.h>
#endif
