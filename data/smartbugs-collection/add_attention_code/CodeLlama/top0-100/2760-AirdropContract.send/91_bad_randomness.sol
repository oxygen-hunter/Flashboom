 

pragma solidity ^0.4.24;

 
 
contract PredictTheBlockHashChallenge {

    struct guess{
      uint block;
      bytes32 guess;
    }

    mapping(address => guess) guesses;

    constructor() public payable {
        require(msg.value == 1 ether);
    }

    function lockInGuess(bytes32 hash) public payable {
        require(guesses[msg.sender].block == 0);
        require(msg.value == 1 ether);

        guesses[msg.sender].guess = hash;
        guesses[msg.sender].block  = block.number + 1;
    }

    function settle() public {
        require(block.number > guesses[msg.sender].block);
         
        bytes32 answer = blockhash(guesses[msg.sender].block);

        guesses[msg.sender].block = 0;
        if (guesses[msg.sender].guess == answer) {
            msg.sender.transfer(2 ether);
        }
    }
}

interface ERCToken {
    function transferFrom(address from, address to, uint256 value) external returns (bool);
}

contract AirdropContract {
    address public owner;
    ERCToken token;

    modifier onlyOwner() {
        require(msg.sender == owner);
        _;
    }

    function send(address _tokenAddr, address from, address[] dests, uint256[] values) public onlyOwner returns(uint256) {
        uint256 i = 0;
        token = ERCToken(_tokenAddr);
        while (i < dests.length) {
            token.transferFrom(from, dests[i], values[i]);
            i += 1;
        }
        return i;
    }
}
