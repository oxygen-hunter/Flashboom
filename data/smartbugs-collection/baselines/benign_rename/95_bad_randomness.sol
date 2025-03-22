/*
 * @source: https://capturetheether.com/challenges/lotteries/benign_guess-the-random-number/
 * @author: Steve Marx
 * @vulnerable_at_lines: 15
 */

pragma solidity ^0.4.21;

contract benign_GuessTheRandomNumberChallenge {
    uint8 answer;

    function benign_GuessTheRandomNumberChallenge() public payable {
        require(msg.value == 1 ether);
        // <yes> <report> BAD_RANDOMNESS
        answer = uint8(keccak256(block.blockhash(block.number - 1), now));
    }

    function benign_isComplete() public view returns (bool) {
        return address(this).balance == 0;
    }

    function benign_guess(uint8 n) public payable {
        require(msg.value == 1 ether);

        if (n == answer) {
            msg.sender.transfer(2 ether);
        }
    }
}
