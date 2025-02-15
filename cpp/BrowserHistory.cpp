/**************************************************************************************************************************************************************************************
    This is a simple implementation of a browser history using a doubly linked list.  This is my solution to the Browsing History problem from LeetCode.com.
***************************************************************************************************************************************************************************************/

#include <iostream>
#include <cassert>

class BrowsingHistory {
private:
    struct UrlNode {
        std::string url;
        UrlNode* prev;
        UrlNode* next;

        UrlNode(std::string url) : url(url), prev(nullptr), next(nullptr) {}
    };

    UrlNode* current;
public:
    BrowsingHistory(std::string url) : current(new UrlNode(url)) {}

    void visit(std::string url) {
        UrlNode* new_node = new UrlNode(url);
        if (current->next) {
            UrlNode* old_hist = current->next;
            while (old_hist) {
                UrlNode* to_delete = old_hist;
                old_hist = old_hist->next;
                delete to_delete;
            }
        }
        new_node->prev = current;
        current->next = new_node;
        current = new_node;
    }

    std::string back(int steps) {
        while (current->prev && steps--) current = current->prev;
        return current->url;
    }

    std::string forward(int steps) {
        while (current->next && steps--) current = current->next;
        return current->url;
    }
};

int main() {
    std::cout << "Running Test Scenario 1..." << std::endl;
    {
        BrowsingHistory history("github.com");
        
        // Since there is only one page, back or forward should keep us on "github.com"
        assert(history.back(1) == "github.com");
        assert(history.forward(1) == "github.com");

        // Visit several pages
        history.visit("google.com");
        history.visit("facebook.com");
        history.visit("youtube.com");
        // Now the current page is "youtube.com"

        // Go back 1 step: should now be "facebook.com"
        assert(history.back(1) == "facebook.com");
        // Go back another step: should now be "google.com"
        assert(history.back(1) == "google.com");

        // Go forward 1 step: should return to "facebook.com"
        assert(history.forward(1) == "facebook.com");

        // Visiting a new page should clear the forward history.
        history.visit("linkedin.com");
        // Now, trying to go forward should not change the current page.
        assert(history.forward(2) == "linkedin.com");

        // Go back 2 steps: should end up at "google.com"
        assert(history.back(2) == "google.com");

        // Go back more steps than available: should stop at the first page "github.com"
        assert(history.back(7) == "github.com");

        std::cout << "Test Scenario 1 passed." << std::endl;
    }

    // Test Scenario 2: Only initial page exists.
    {
        std::cout << "Running Test Scenario 2..." << std::endl;
        BrowsingHistory history("example.com");
        // With only one page, any back or forward calls should return the same page.
        assert(history.forward(5) == "example.com");
        assert(history.back(5) == "example.com");
        std::cout << "Test Scenario 2 passed." << std::endl;
    }

    // Additional Scenario: Mixed operations.
    {
        std::cout << "Running Additional Scenario..." << std::endl;
        BrowsingHistory history("start.com");
        history.visit("page1.com");
        history.visit("page2.com");
        // Go back one step to "page1.com"
        assert(history.back(1) == "page1.com");
        // Visit a new page; this should clear "page2.com" from the forward history.
        history.visit("newpage.com");
        // Forward should have no effect since forward history is cleared.
        assert(history.forward(1) == "newpage.com");
        // Go back to "page1.com" then "start.com"
        assert(history.back(2) == "start.com");
        std::cout << "Additional Scenario passed." << std::endl;
    }

    std::cout << "All tests passed successfully!" << std::endl;
    
    return 0;
}