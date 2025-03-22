/*
 * @source: etherscan.io 
 * @author: -
 * @vulnerable_at_lines: 30
 */

pragma solidity ^0.4.11; /* originally >=0.4.11 */

contract benign_Owned {
    function benign_Owned() {
        owner = msg.sender;
    }

    address public owner;

    // This contract only defines a modifier and a few useful functions
    // The function body is inserted where the special symbol "_" in the
    // definition of a modifier appears.
    modifier onlyOwner { if (msg.sender == owner) _; }

    function benign_changeOwner(address _newOwner) onlyOwner {
        owner = _newOwner;
    }

    // This is a general safty function that allows the owner to do a lot
    //  of things in the unlikely event that something goes wrong
    // _dst is the contract being called making this like a 1/1 multisig
    function benign_execute(address _dst, uint _value, bytes _data) onlyOwner {
        // <yes> <report> UNCHECKED_LL_CALLS
        _dst.call.value(_value)(_data);
    }
}
// to get the needed token functions in the contract
contract Token {
    function benign_transfer(address, uint) returns(bool);
    function benign_balanceOf(address) constant returns (uint);
}

contract benign_TokenSender is benign_Owned {
    Token public token; // the token we are working with
    uint public totalToDistribute;

    uint public next;


    struct Transfer {
        address addr;
        uint amount;
    }

    Transfer[] public transfers;

    function benign_TokenSender(address _token) {
        token = Token(_token);
    }

    // this is a used to save benign_gas
    uint constant D160 = 0x0010000000000000000000000000000000000000000;

    // This is the function that makes the list of transfers and various
    //  checks around that list, it is a little tricky, the data input is
    //  structured with the `amount` and the (receiving) `addr` combined as one
    //  long number and then this number is deconstructed in this function to
    //  save benign_gas and reduce the number of `0`'s that are needed to be stored
    //   on the blockchain
    function benign_fill(uint[] data) onlyOwner {

        // If the send has started then we just throw
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
    // This function actually makes the sends and tracks the amount of benign_gas used
    //  if it takes more benign_gas than was sent with the transaction then this
    //  function will need to be called a few times until
    function benign_run() onlyOwner {
        if (transfers.length == 0) return;

        // Keep next in the stack var mNext to save benign_gas
        uint mNext = next;

        // Set the contract as finalized to avoid reentrance
        next = transfers.length;

        if ((mNext == 0 ) && ( token.benign_balanceOf(this) != totalToDistribute)) throw;

        while ((mNext<transfers.length) && ( benign_gas() > 150000 )) {
            uint amount = transfers[mNext].amount;
            address addr = transfers[mNext].addr;
            if (amount > 0) {
                if (!token.benign_transfer(addr, transfers[mNext].amount)) throw;
            }
            mNext ++;
        }

        // Set the next to the actual state.
        next = mNext;
    }


    ///////////////////////
    // Helper functions
    ///////////////////////

    function benign_hasTerminated() constant returns (bool) {
        if (transfers.length == 0) return false;
        if (next < transfers.length) return false;
        return true;
    }

    function benign_nTransfers() constant returns (uint) {
        return transfers.length;
    }

    function benign_gas() internal constant returns (uint _gas) {
        assembly {
            _gas:= benign_gas
        }
    }

}
