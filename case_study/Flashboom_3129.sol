contract wordbot { 
    function getWords(uint _wordcount) public view returns (bytes6[]) {} 
}
contract test {
    wordbot wordbot_contract = wordbot(0xA95E23);
    uint wordcount = 12;
    string[12] public human_readable_blockhash;

    modifier one_time_use {
    require(keccak256(abi.encodePacked
    (human_readable_blockhash[0])) == keccak256(abi.encodePacked("")));
        _;
    }
    function record_human_readable_blockhash() one_time_use public {
        bytes6[] memory word_sequence = wordbot_contract.getWords(wordcount);
        for (uint i = 0; i < wordcount; i++) {
            bytes6 word = word_sequence[i];
            bytes memory toBytes = new bytes(6);
            for (uint j = 0; j < 6; j++) toBytes[j] = word[j];
            human_readable_blockhash[i] = string(toBytes);
        }
    }
}