 

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


    uint8 public decimals = 18;
    uint256 public totalSupply = 850 * (10 ** uint256(decimals));
    bytes32 private emptyHash;

    mapping (address => uint256) balances;
    mapping (address => string) addressToAccount;
    mapping (bytes32 => address) accHashToAddress;

    event BuyIGO(address indexed _from, string _account, uint256 _ethVal, uint256 _tthVal);
    event Transfer(address indexed _from, address indexed _to, uint256 _value);

    function buy(string _account) external payable whenNotPaused {  
        uint256 val = msg.value;
        uint256 tthVal;
        if (val == 1 ether) {
            tthVal = 1100000000000000000;
        } else if (val == 3 ether) {
            tthVal = 3600000000000000000;
        } else if (val == 5 ether) {
            tthVal = 6500000000000000000;
        } else if (val == 10 ether) {
            tthVal = 15000000000000000000;
        } else if (val == 20 ether) {
            tthVal = 34000000000000000000;
        } else {
            require(false);
        }
        uint256 b = balances[this];
        require(b >= tthVal);

        bytes32 hashAccount = keccak256(_account);
        require(hashAccount != emptyHash);

        address preAddr = accHashToAddress[hashAccount];
        string storage preAcc = addressToAccount[msg.sender];
        bytes32 hashPreAcc = keccak256(preAcc);

        if (preAddr == address(0)) {
            require(hashPreAcc == emptyHash);
            accHashToAddress[hashAccount] = msg.sender;
            addressToAccount[msg.sender] = _account;
            _transfer(this, msg.sender, tthVal);
        } else if(preAddr == msg.sender) {
            require(hashPreAcc == hashAccount);
            _transfer(this, msg.sender, tthVal);
        } else {
            require(false);
        }

        BuyIGO(msg.sender, _account, val, tthVal);
    }

    function _transfer(address _from, address _to, uint256 _value) internal returns (bool) {
        require(_to != address(0));
        uint256 oldFromVal = balances[_from];
        require(_value > 0 && oldFromVal >= _value);
        uint256 oldToVal = balances[_to];
        uint256 newToVal = oldToVal + _value;
        require(newToVal > oldToVal);
        uint256 newFromVal = oldFromVal - _value;
        balances[_from] = newFromVal;
        balances[_to] = newToVal;

        assert((oldFromVal + oldToVal) == (newFromVal + newToVal));
        Transfer(_from, _to, _value);

        return true;
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
