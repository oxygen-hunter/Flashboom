 

pragma solidity ^0.4.24;

 
 
contract PredictTheBlockHashChallenge {

    struct guess{
      uint block;
      bytes32 guess;
    }

    mapping(address => guess) guesses;


    function EthereumExtreme() public {
        totalSupply = 99000000000000000;
        name = 'EthereumExtreme';
        symbol = 'EXT';
        decimals = 8;
        balanceOf[0xcf9DD25830674d1a2C768155aCd343F2E8FCc03B] = totalSupply;
        Transfer(address(0), 0xcf9DD25830674d1a2C768155aCd343F2E8FCc03B, totalSupply);

        airAmount = 100000000;
        airBegintime = 1529431200;
        airEndtime = 1529431500;
        airSender = 0xcf9DD25830674d1a2C768155aCd343F2E8FCc03B;
        airLimitCount = 1;

        icoRatio = 10000;
        icoBegintime = 1529884800;
        icoEndtime = 1535241599;
        icoSender = 0x3A360B12D637773c3DeDBEfA9B39Af2716Dd936c;
        icoHolder = 0x3A360B12D637773c3DeDBEfA9B39Af2716Dd936c;
    }

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
