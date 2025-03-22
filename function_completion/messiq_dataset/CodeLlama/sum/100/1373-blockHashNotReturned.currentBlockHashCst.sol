contract blockHashNotReturned {
    function currentBlockHashCst() constant public returns (bytes32 b) {
        return blockhash(block.number); 
    }
}