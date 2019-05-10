class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:

        result = {len(s): [' ']}
        def get_sentence(i):
            if i in result:
                return result[i]
            else:
                comp = []
                for j in range(i, len(s)+1):
                    item = s[i:j]
                    if item in wordDict:
                        tail = get_sentence(j)
                        if tail:
                            for one in tail:
                                if one != ' ':
                                    new_one = item + ' ' + one
                                    comp.append(new_one)
                                else:
                                    comp.append(item)
                        # else:
                        #     comp.append(item)
                result[i] = comp
                return comp

        get_sentence(0)
        return result[0]        
        
        
        
