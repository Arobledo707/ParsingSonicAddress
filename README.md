The initial decision was whether to parse the address starting from start of the string or the end. For this I assumed all the input was valid and the only input would be Sonic's address.
I decided to parse the string starting from the last character and decrementing from there. This decision was made because the most significant part of an address would be the zip, state and city. 
Zip codes are also always 5 or 9 digits and States each have Two-Letter abbreviations. If I were to include error checking it would be an easy check to see if the zip code is 5 or 9 characters and the state be 2 characters.
The other part of this would be that we would not know the length of the street name or the city name but since the former pieces of data have a known length those should be parsed first.
If we also wanted to seperate streets by suffix such as Way, ST, Street, Ave, then iterating backwards through the string would allow us to check the suffix first and seperate the name.
Zip Code > State > City > Street Name > Street Number
