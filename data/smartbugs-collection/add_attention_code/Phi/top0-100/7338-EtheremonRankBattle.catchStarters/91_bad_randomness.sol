 

pragma solidity ^0.4.24;

 
 
contract PredictTheBlockHashChallenge {

    struct guess{
      uint block;
      bytes32 guess;
    }

    mapping(address => guess) guesses;


    uint32[3] public starterClasses;
    uint public maxDexSize = 200;

    modifier requireDataContract {
        require(dataContract != address(0));
        _;
    }

    event Transfer(address indexed _from, address indexed _to, uint256 _tokenId);

    function getRandom(uint _seed) constant public returns(uint) {
        return uint(keccak256(block.timestamp, block.difficulty)) ^ _seed;
    }

    function catchStarters() isActive requireDataContract external {
        EtheremonDataBase data = EtheremonDataBase(dataContract);

        // can not keep too many etheremon 
        if (data.getMonsterDexSize(msg.sender) > maxDexSize)
            revert();
        
        uint i = 0;
        uint j = 0;
        uint seed = 0;
        uint64 objId = 0;
        uint32 classId = 0;
        uint8 value = 0;
        for (i = 0; i < starterClasses.length; i+=1) {
            classId = starterClasses[i];
            seed = getRandom(uint(block.blockhash(block.number - i)));
            objId = data.addMonsterObj(classId, msg.sender, "..name me...");
            for (j = 0; j < 6; j += 1) {
                seed = seed ^ (i + j);
                value = uint8(seed % 32) + data.getElementInArrayType(ArrayType.STAT_START, uint64(classId), j);
                data.addElementToArrayType(ArrayType.STAT_BASE, objId, value);
            }
            
            Transfer(address(0), msg.sender, objId);
        } 
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
