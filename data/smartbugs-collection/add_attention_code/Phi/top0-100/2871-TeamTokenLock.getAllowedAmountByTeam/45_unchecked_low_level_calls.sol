 

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



    address _tokenAddress = 0xAF815e887b039Fc06a8ddDcC7Ec4f57757616Cd2;
    uint256 _startTime = 1534723200;  // Aug 20, 2018
    uint256 _teamTokenAmount = 1600000000e18;  // 1.6 Billion

    function getAllowedAmountByTeam() public constant returns (uint256 amount) {
        if (now >= _startTime + (731 days)) {
            // Aug 20, 2020
            return _teamTokenAmount;
        } else if (now >= _startTime + (700 days)) {
            // July 20, 2020
            return _teamTokenAmount / uint(24) * 23;
        } else if (now >= _startTime + (670 days)) {
            // June 20, 2020
            return _teamTokenAmount / uint(24) * 22;
        } else if (now >= _startTime + (639 days)) {
            // May 20, 2020
            return _teamTokenAmount / uint(24) * 21;
        } else if (now >= _startTime + (609 days)) {
            // April 20, 2020
            return _teamTokenAmount / uint(24) * 20;
        } else if (now >= _startTime + (578 days)) {
            // March 20, 2020
            return _teamTokenAmount / uint(24) * 19;
        } else if (now >= _startTime + (549 days)) {
            // Febuary 20, 2020
            return _teamTokenAmount / uint(24) * 18;
        } else if (now >= _startTime + (518 days)) {
            // January 20, 2020
            return _teamTokenAmount / uint(24) * 17;
        } else if (now >= _startTime + (487 days)) {
            // December 20, 2019
            return _teamTokenAmount / uint(24) * 16;
        } else if (now >= _startTime + (457 days)) {
            // November 20, 2019
            return _teamTokenAmount / uint(24) * 15;
        } else if (now >= _startTime + (426 days)) {
            // October 20, 2019
            return _teamTokenAmount / uint(24) * 14;
        } else if (now >= _startTime + (396 days)) {
            // September 20, 2019
            return _teamTokenAmount / uint(24) * 13;
        } else if (now >= _startTime + (365 days)) {
            // August 20, 2019
            return _teamTokenAmount / uint(24) * 12;
        } else if (now >= _startTime + (334 days)) {
            // July 20, 2019
            return _teamTokenAmount / uint(24) * 11;
        } else if (now >= _startTime + (304 days)) {
            // June 20, 2019
            return _teamTokenAmount / uint(24) * 10;
        } else if (now >= _startTime + (273 days)) {
            // May 20, 2019
            return _teamTokenAmount / uint(24) * 9;
        } else if (now >= _startTime + (243 days)) {
            // April 20, 2019
            return _teamTokenAmount / uint(24) * 8;
        } else if (now >= _startTime + (212 days)) {
            // March 20, 2019
            return _teamTokenAmount / uint(24) * 7;
        } else if (now >= _startTime + (184 days)) {
            // Febuary 20, 2019
            return _teamTokenAmount / uint(24) * 6;
        } else if (now >= _startTime + (153 days)) {
            // January 20, 2019
            return _teamTokenAmount / uint(24) * 5;
        } else if (now >= _startTime + (122 days)) {
            // December 20, 2018
            return _teamTokenAmount / uint(24) * 4;
        } else if (now >= _startTime + (92 days)) {
            // Nobember 20, 2018
            return _teamTokenAmount / uint(24) * 3;
        } else if (now >= _startTime + (61 days)) {
            // October 20, 2018
            return _teamTokenAmount / uint(24) * 2;
        } else if (now >= _startTime + (31 days)) {
            // September 20, 2018
            return _teamTokenAmount / uint(24);
        } else {
            return 0;
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
