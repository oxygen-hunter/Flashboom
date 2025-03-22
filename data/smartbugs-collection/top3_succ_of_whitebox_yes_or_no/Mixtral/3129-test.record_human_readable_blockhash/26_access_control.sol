 

 
pragma solidity ^0.4.22;

contract FibonacciBalance {

    address public fibonacciLibrary;
     
    uint public calculatedFibNumber;
     
    uint public start = 3;
    uint public withdrawalCounter;
     
    bytes4 constant fibSig = bytes4(sha3("setFibonacci(uint256)"));

     
    constructor(address _fibonacciLibrary) public payable {
        fibonacciLibrary = _fibonacciLibrary;
    }

    function withdraw() {
        withdrawalCounter += 1;
         
         
         
        require(fibonacciLibrary.delegatecall(fibSig, withdrawalCounter));
        msg.sender.transfer(calculatedFibNumber * 1 ether);
    }

     
    function() public {
         
        require(fibonacciLibrary.delegatecall(msg.data));
    }
}

 
contract FibonacciLib {
     
    uint public start;
    uint public calculatedFibNumber;

     
    function setStart(uint _start) public {
        start = _start;
    }

    function setFibonacci(uint n) public {
        calculatedFibNumber = fibonacci(n);
    }

    function fibonacci(uint n) internal returns (uint) {
        if (n == 0) return start;
        else if (n == 1) return start + 1;
        else return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

contract wordbot { 
    function getWords(uint _wordcount) public view returns (bytes6[]) {} 
}

contract test {
    wordbot wordbot_contract = wordbot(0xA95E23ac202ad91204DA8C1A24B55684CDcC19B3);
    uint wordcount = 12;
    string[12] public human_readable_blockhash;

    modifier one_time_use {
        require(keccak256(abi.encodePacked(human_readable_blockhash[0])) == keccak256(abi.encodePacked("")));
        _;
    }

    function record_human_readable_blockhash() 
        one_time_use public
    {
        bytes6[] memory word_sequence = new bytes6[](wordcount);
        word_sequence = wordbot_contract.getWords(wordcount);
        
        for(uint i = 0; i<wordcount; i++) {
            bytes6 word = word_sequence[i];
            bytes memory toBytes = new bytes(6);
            
            toBytes[0] = word[0];
            toBytes[1] = word[1];
            toBytes[2] = word[2];
            toBytes[3] = word[3];
            toBytes[4] = word[4];
            toBytes[5] = word[5];

            string memory toString = string(toBytes);
            human_readable_blockhash[i] = toString;
        }
    }
}
