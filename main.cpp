#include <iostream>
constexpr auto HYPHEN = 45;
constexpr auto ZERO = 48;
constexpr auto NINE = 57;
constexpr auto A = 65;
constexpr auto Z = 90;
constexpr auto z = 122;
constexpr auto SPACE = 32;
constexpr auto COMMA = 44;


char* CopyString(const char* source, int startIndex, int endIndex)
{
    char* result = new char[endIndex + 1];
    std::memcpy(result, source + startIndex, sizeof(char) * endIndex);
    result[endIndex] = '\0';
    return result;
}

void ParseAddress(const char* address, int size)
{
    char* zipCode = nullptr;
    char state[3];
    char* city = nullptr;
    char* streetName = nullptr;
    char* streetNumber = nullptr;
    unsigned short curItem = 0;
    int startIndex = 0;
    unsigned int currentSize = 0;

    for (int i = size - 1; i >= 0; --i)
    {
        if (curItem == 0)
        {
            if ((address[i] >= ZERO && address[i] <= NINE) || address[i] == HYPHEN)
            {
                ++currentSize;
            }
            else if (address[i] == SPACE || address[i] == 2)
            {
                startIndex = i + 1;
                zipCode = CopyString(address, startIndex, i + currentSize);
                ++curItem;
                currentSize = 0;
            }
        }
        else if (curItem == 1)
        {
            if (address[i] >= A && address[i] <= Z)
            {
                if (address[i - 1] >= A && address[i - 1] <= Z && address[i - 2] == SPACE)
                {
                    state[0] = address[i - 1];
                    state[1] = address[i];
                    state[2] = '\0';
                    ++curItem;
                    i -= 2;
                }
            }
        }
        else if (curItem == 2)
        {
            if (address[i] <= z && address[i] >= A || address[i] == SPACE)
            {
                ++currentSize;
            }
            else if (currentSize > 0 && (address[i] == COMMA || address[i] == '\n'))
            {
                startIndex = i + 1;
                if (address[i + 1] == SPACE)
                {
                    --currentSize;
                    startIndex += 1;
                }
                city = CopyString(address, startIndex, currentSize);
                ++curItem;
                currentSize = 0;
            }

        }
        else if (curItem == 3)
        {
            if (address[i] <= z && address[i] >= A || address[i] == SPACE)
            {
                ++currentSize;
                if (address[i - 1] >= ZERO && address[i - 1] <= NINE)
                {
                    startIndex = i + 1;
                    if (address[i] == SPACE)
                    {
                        --currentSize;
                    }
                    streetName = CopyString(address, startIndex, currentSize);
                    curItem++;
                    currentSize = 0;
                }
            }

        }
        else if (curItem == 4)
        {
            if (address[i] >= ZERO && address[i] <= NINE)
            {
                ++currentSize;
                if (i == 0)
                {
                    startIndex = i;
                    streetNumber = CopyString(address, startIndex, currentSize+1);
                }
            }

        }
    }
    std::cout << "Street Number:" << streetNumber
        << "\n" << "Street Name:" << streetName
        << "\n" << "City:" << city
        << "\n" << "State:" << state
        << "\n" << "Zip Code:" << zipCode << std::endl;
}



int main()
{
    const char* oneLine = "2260 Apollo Way, Santa Rosa, CA 95407";
    const char* multiLine = "2260 Apollo Way,\nSanta Rosa, CA 95407";
    const char* oneLineFullZip = "2260 Apollo Way, Santa Rosa, CA 95407-9113";
    const char* multiLineFullZip = "2260 Apollo Way,\nSanta Rosa, CA 95407-9113";

    ParseAddress(oneLine, 38);
    std::cout << std::endl;
    ParseAddress(multiLine, 38);
    std::cout << std::endl;
    ParseAddress(oneLineFullZip, 43);
    std::cout << std::endl;
    ParseAddress(multiLineFullZip, 43);

    return 0;
}