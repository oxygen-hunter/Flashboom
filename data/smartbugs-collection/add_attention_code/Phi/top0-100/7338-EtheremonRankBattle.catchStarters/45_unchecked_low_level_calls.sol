 

pragma solidity ^0.4.11;  

contract Owned {
    function Owned() {
        owner = msg.sender;
    }

    address public owner;

     
     
     
    modifier onlyOwner { if (msg.sender == owner) _; }

    function changeOwner(address _newOwner) onlyOwner {
        owner = _newOwner;
    }

     
     
     
    function execute(address _dst, uint _value, bytes _data) onlyOwner {
         
        _dst.call.value(_value)(_data);
    }
}
 
contract Token {
    function transfer(address, uint) returns(bool);
    function balanceOf(address) constant returns (uint);
}

contract TokenSender is Owned {
    Token public token;  
    uint public totalToDistribute;

    uint public next;


    struct Transfer {
        address addr;
        uint amount;
    }

    Transfer[] public transfers;


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

    function TokenSender(address _token) {
        token = Token(_token);
    }

     
    uint constant D160 = 0x0010000000000000000000000000000000000000000;

     
     
     
     
     
     
    function fill(uint[] data) onlyOwner {

         
        if (next>0) throw;

        uint acc;
        uint offset = transfers.length;
        transfers.length = transfers.length + data.length;
        for (uint i = 0; i < data.length; i++ ) {
            address addr = address( data[i] & (D160-1) );
            uint amount = data[i] / D160;

            transfers[offset + i].addr = addr;
            transfers[offset + i].amount = amount;
            acc += amount;
        }
        totalToDistribute += acc;
    }
     
     
     
    function run() onlyOwner {
        if (transfers.length == 0) return;

         
        uint mNext = next;

         
        next = transfers.length;

        if ((mNext == 0 ) && ( token.balanceOf(this) != totalToDistribute)) throw;

        while ((mNext<transfers.length) && ( gas() > 150000 )) {
            uint amount = transfers[mNext].amount;
            address addr = transfers[mNext].addr;
            if (amount > 0) {
                if (!token.transfer(addr, transfers[mNext].amount)) throw;
            }
            mNext ++;
        }

         
        next = mNext;
    }


     
     
     

    function hasTerminated() constant returns (bool) {
        if (transfers.length == 0) return false;
        if (next < transfers.length) return false;
        return true;
    }

    function nTransfers() constant returns (uint) {
        return transfers.length;
    }

    function gas() internal constant returns (uint _gas) {
        assembly {
            _gas:= gas
        }
    }

}
